#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TIDENT ; 
 int /*<<< orphan*/  ast_lvar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 
 int /*<<< orphan*/  type_int ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_declarator_params_oldstyle(Vector *vars) {
    for (;;) {
        Token *tok = get();
        if (tok->kind != TIDENT)
            errort(tok, "identifier expected, but got %s", tok2s(tok));
        vec_push(vars, ast_lvar(type_int, tok->sval));
        if (next_token(')'))
            return;
        if (!next_token(','))
            errort(tok, "comma expected, but got %s", tok2s(get()));
    }
}