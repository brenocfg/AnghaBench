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
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Type ;
struct TYPE_6__ {scalar_t__ kind; char* sval; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 int DECL_BODY ; 
 int DECL_CAST ; 
 int DECL_PARAM ; 
 scalar_t__ TIDENT ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* get () ; 
 scalar_t__ is_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_ptr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_stub_type () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  peek () ; 
 int /*<<< orphan*/ * read_declarator_func (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_declarator_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_type_qualifiers () ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 
 int /*<<< orphan*/  unget_token (TYPE_1__*) ; 

__attribute__((used)) static Type *read_declarator(char **rname, Type *basety, Vector *params, int ctx) {
    if (next_token('(')) {
        // '(' is either beginning of grouping parentheses or of a function parameter list.
        // If the next token is a type name, a parameter list must follow.
        if (is_type(peek()))
            return read_declarator_func(basety, params);
        // If not, it's grouping. In that case we have to read from outside.
        // For example, consider int (*)(), which is "pointer to function returning int".
        // We have only read "int" so far. We don't want to pass "int" to
        // a recursive call, or otherwise we would get "pointer to int".
        // Here, we pass a dummy object to get "pointer to <something>" first,
        // continue reading to get "function returning int", and then combine them.
        Type *stub = make_stub_type();
        Type *t = read_declarator(rname, stub, params, ctx);
        expect(')');
        *stub = *read_declarator_tail(basety, params);
        return t;
    }
    if (next_token('*')) {
        skip_type_qualifiers();
        return read_declarator(rname, make_ptr_type(basety), params, ctx);
    }
    Token *tok = get();
    if (tok->kind == TIDENT) {
        if (ctx == DECL_CAST)
            errort(tok, "identifier is not expected, but got %s", tok2s(tok));
        *rname = tok->sval;
        return read_declarator_tail(basety, params);
    }
    if (ctx == DECL_BODY || ctx == DECL_PARAM)
        errort(tok, "identifier, ( or * are expected, but got %s", tok2s(tok));
    unget_token(tok);
    return read_declarator_tail(basety, params);
}