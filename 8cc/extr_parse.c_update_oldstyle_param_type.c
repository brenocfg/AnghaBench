#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_3__ {scalar_t__ kind; int /*<<< orphan*/  varname; int /*<<< orphan*/  ty; struct TYPE_3__* declvar; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 scalar_t__ AST_DECL ; 
 scalar_t__ AST_LVAR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_oldstyle_param_type(Vector *params, Vector *vars) {
    for (int i = 0; i < vec_len(vars); i++) {
        Node *decl = vec_get(vars, i);
        assert(decl->kind == AST_DECL);
        Node *var = decl->declvar;
        assert(var->kind == AST_LVAR);
        for (int j = 0; j < vec_len(params); j++) {
            Node *param = vec_get(params, j);
            assert(param->kind == AST_LVAR);
            if (strcmp(param->varname, var->varname))
                continue;
            param->ty = var->ty;
            goto found;
        }
        error("missing parameter: %s", var->varname);
    found:;
    }
}