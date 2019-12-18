#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Type ;
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 int /*<<< orphan*/  KELLIPSIS ; 
 int /*<<< orphan*/ * ast_lvar (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ensure_not_void (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/ * get () ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ *,char) ; 
 scalar_t__ next_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * peek () ; 
 int /*<<< orphan*/ * read_func_param (char**,int) ; 
 int /*<<< orphan*/  tok2s (int /*<<< orphan*/ *) ; 
 scalar_t__ vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_declarator_params(Vector *types, Vector *vars, bool *ellipsis) {
    bool typeonly = !vars;
    *ellipsis = false;
    for (;;) {
        Token *tok = peek();
        if (next_token(KELLIPSIS)) {
            if (vec_len(types) == 0)
                errort(tok, "at least one parameter is required before \"...\"");
            expect(')');
            *ellipsis = true;
            return;
        }
        char *name;
        Type *ty = read_func_param(&name, typeonly);
        ensure_not_void(ty);
        vec_push(types, ty);
        if (!typeonly)
            vec_push(vars, ast_lvar(ty, name));
        tok = get();
        if (is_keyword(tok, ')'))
            return;
        if (!is_keyword(tok, ','))
            errort(tok, "comma expected, but got %s", tok2s(tok));
    }
}