#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_7__ {scalar_t__ kind; int /*<<< orphan*/  space; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 scalar_t__ TIDENT ; 
 scalar_t__ TNEWLINE ; 
 TYPE_1__* copy_token (TYPE_1__*) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/ * make_vector () ; 
 TYPE_1__* map_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Vector *read_funclike_macro_body(Map *param) {
    Vector *r = make_vector();
    for (;;) {
        Token *tok = lex();
        if (tok->kind == TNEWLINE)
            return r;
        if (tok->kind == TIDENT) {
            Token *subst = map_get(param, tok->sval);
            if (subst) {
                subst = copy_token(subst);
                subst->space = tok->space;
                vec_push(r, subst);
                continue;
            }
        }
        vec_push(r, tok);
    }
}