#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Type ;
struct TYPE_4__ {int /*<<< orphan*/ * lvarinit; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 TYPE_1__* ast_lvar (int /*<<< orphan*/ *,char*) ; 
 char* make_label () ; 
 int /*<<< orphan*/ * read_decl_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_compound_literal(Type *ty) {
    char *name = make_label();
    Vector *init = read_decl_init(ty);
    Node *r = ast_lvar(ty, name);
    r->lvarinit = init;
    return r;
}