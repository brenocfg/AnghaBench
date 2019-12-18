#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_9__ {TYPE_1__* ty; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 scalar_t__ KIND_FUNC ; 
 TYPE_2__* ast_funcdesg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  env () ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  is_keyword (int /*<<< orphan*/ *,char) ; 
 TYPE_1__* make_func_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  make_vector () ; 
 TYPE_2__* map_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * peek () ; 
 int /*<<< orphan*/  type_int ; 
 int /*<<< orphan*/  warnt (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static Node *read_var_or_func(char *name) {
    Node *v = map_get(env(), name);
    if (!v) {
        Token *tok = peek();
        if (!is_keyword(tok, '('))
            errort(tok, "undefined variable: %s", name);
        Type *ty = make_func_type(type_int, make_vector(), true, false);
        warnt(tok, "assume returning int: %s()", name);
        return ast_funcdesg(ty, name);
    }
    if (v->ty->kind == KIND_FUNC)
        return ast_funcdesg(v->ty, name);
    return v;
}