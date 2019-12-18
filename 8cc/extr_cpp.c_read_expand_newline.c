#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_13__ {scalar_t__ kind; char* sval; int /*<<< orphan*/  hideset; } ;
typedef  TYPE_1__ Token ;
struct TYPE_14__ {int kind; int /*<<< orphan*/  (* fn ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  Set ;
typedef  TYPE_2__ Macro ;

/* Variables and functions */
#define  MACRO_FUNC 130 
#define  MACRO_OBJ 129 
#define  MACRO_SPECIAL 128 
 scalar_t__ TIDENT ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/  macros ; 
 TYPE_2__* map_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  next (char) ; 
 TYPE_1__* peek_token () ; 
 int /*<<< orphan*/  propagate_space (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * read_args (TYPE_1__*,TYPE_2__*) ; 
 TYPE_1__* read_expand () ; 
 int /*<<< orphan*/ * set_add (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ set_has (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_intersection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/ * subst (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unget_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Token *read_expand_newline() {
    Token *tok = lex();
    if (tok->kind != TIDENT)
        return tok;
    char *name = tok->sval;
    Macro *macro = map_get(macros, name);
    if (!macro || set_has(tok->hideset, name))
        return tok;

    switch (macro->kind) {
    case MACRO_OBJ: {
        Set *hideset = set_add(tok->hideset, name);
        Vector *tokens = subst(macro, NULL, hideset);
        propagate_space(tokens, tok);
        unget_all(tokens);
        return read_expand();
    }
    case MACRO_FUNC: {
        if (!next('('))
            return tok;
        Vector *args = read_args(tok, macro);
        Token *rparen = peek_token();
        expect(')');
        Set *hideset = set_add(set_intersection(tok->hideset, rparen->hideset), name);
        Vector *tokens = subst(macro, args, hideset);
        propagate_space(tokens, tok);
        unget_all(tokens);
        return read_expand();
    }
    case MACRO_SPECIAL:
        macro->fn(tok);
        return read_expand();
    default:
        error("internal error");
    }
}