/* Copyright 2016-2017 Sergio Oller, Barcelona
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "fr_lang.h"

static const char *fr_whitespace = " \t\n\r";
static const char *fr_singlecharsymbols = "€";
static const char *fr_prepunctuation = "«\"'``({[";
static const char *fr_punctuation = "»\"'``.,:;!?(){}[]";

/* The tokenizer is one of the first steps in the text analysis. It splits text
 * into a list of tokens.
 * Each token can have attributes, typically it has:
 * - a name: with the actual token or word, having removed punctuation ("1984",
 * "potato", ...)
 * - whitespace: the whitespace characters after the token
 * - prepunctuation: the prepunctuation characters in the token
 * - postpunctuation: the punctuation characters after the token
 *
 * Example: Bonjour!, comment tu t'appelles?
 * This would have three tokens:
 * - name: "Bonjour" prepunct: "" punct: "!," whitespace: " "
 * - name: "comment" prepunct: "" punct: "" whitespace: " "
 * - name: "tu" prepunct: "" punct: "" whitespace: " "
 * - name: "t'appelles" prepunct: "" punct: "?" whitespace: ""
 *
 * The tokenizer gets the text from :
 * const char *text = utt_input_text(u);
 * And stores the tokens in the "Token" relation
 * r = utt_relation_create(u, "Token");
 *
 * The default_tokenization defined in src/synth/cst_synth.c relies on the
 * tokenstream
 * and is enough for our needs.
 */
void fr_init_tokenizer(cst_voice *v)
{
    /*feat_set(v->features, "tokenizer_func",
     * uttfunc_val(&default_tokenization));*/
    feat_set_string(v->features, "text_whitespace", fr_whitespace);
    feat_set_string(v->features, "text_postpunctuation", fr_punctuation);
    feat_set_string(v->features, "text_prepunctuation", fr_prepunctuation);
    feat_set_string(v->features, "text_singlecharsymbols",
                    fr_singlecharsymbols);
    feat_set_int(v->features, "text_emoji_as_singlecharsymbols", 1);
}
