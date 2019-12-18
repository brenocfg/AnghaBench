#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_8__ {scalar_t__ kind; char* sval; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TNEWLINE ; 
 scalar_t__ TSTRING ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,...) ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 char* join_paths (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_vector () ; 
 TYPE_1__* read_expand_newline () ; 
 char* read_header_file_name (int*) ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static char *read_cpp_header_name(Token *hash, bool *std) {
    // Try reading a filename using a special tokenizer for #include.
    char *path = read_header_file_name(std);
    if (path)
        return path;

    // If a token following #include does not start with < nor ",
    // try to read the token as a regular token. Macro-expanded
    // form may be a valid header file path.
    Token *tok = read_expand_newline();
    if (tok->kind == TNEWLINE)
        errort(hash, "expected filename, but got newline");
    if (tok->kind == TSTRING) {
        *std = false;
        return tok->sval;
    }
    if (!is_keyword(tok, '<'))
        errort(tok, "< expected, but got %s", tok2s(tok));
    Vector *tokens = make_vector();
    for (;;) {
        Token *tok = read_expand_newline();
        if (tok->kind == TNEWLINE)
            errort(hash, "premature end of header name");
        if (is_keyword(tok, '>'))
            break;
        vec_push(tokens, tok);
    }
    *std = true;
    return join_paths(tokens);
}