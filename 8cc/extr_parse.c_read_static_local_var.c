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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 int /*<<< orphan*/  ast_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ast_static_lvar (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * localenv ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/ * read_decl_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toplevels ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_static_local_var(Type *ty, char *name) {
    Node *var = ast_static_lvar(ty, name);
    Vector *init = NULL;
    if (next_token('=')) {
        Map *orig = localenv;
        localenv = NULL;
        init = read_decl_init(ty);
        localenv = orig;
    }
    vec_push(toplevels, ast_decl(var, init));
}