#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int kind; int /*<<< orphan*/  slen; int /*<<< orphan*/  sval; int /*<<< orphan*/  enc; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 char KGENERIC ; 
#define  TCHAR 132 
#define  TIDENT 131 
#define  TKEYWORD 130 
#define  TNUMBER 129 
#define  TSTRING 128 
 int /*<<< orphan*/ * ast_inttype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ast_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  char_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* get () ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/ * read_expr () ; 
 int /*<<< orphan*/ * read_generic () ; 
 int /*<<< orphan*/ * read_number (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_stmt_expr () ; 
 int /*<<< orphan*/ * read_var_or_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unget_token (TYPE_1__*) ; 

__attribute__((used)) static Node *read_primary_expr() {
    Token *tok = get();
    if (!tok) return NULL;
    if (is_keyword(tok, '(')) {
        if (next_token('{'))
            return read_stmt_expr();
        Node *r = read_expr();
        expect(')');
        return r;
    }
    if (is_keyword(tok, KGENERIC)) {
        return read_generic();
    }
    switch (tok->kind) {
    case TIDENT:
        return read_var_or_func(tok->sval);
    case TNUMBER:
        return read_number(tok);
    case TCHAR:
        return ast_inttype(char_type(tok->enc), tok->c);
    case TSTRING:
        return ast_string(tok->enc, tok->sval, tok->slen);
    case TKEYWORD:
        unget_token(tok);
        return NULL;
    default:
        error("internal error: unknown token kind: %d", tok->kind);
    }
}