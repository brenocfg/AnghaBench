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
typedef  int /*<<< orphan*/  Token ;
struct TYPE_6__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  node2s (TYPE_1__*) ; 
 int /*<<< orphan*/ * peek () ; 
 TYPE_1__* read_assignment_expr () ; 
 int /*<<< orphan*/ * read_generic_list (TYPE_1__**) ; 
 int /*<<< orphan*/  ty2s (int /*<<< orphan*/ ) ; 
 scalar_t__ type_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void** vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_generic() {
    expect('(');
    Token *tok = peek();
    Node *contexpr = read_assignment_expr();
    expect(',');
    Node *defaultexpr = NULL;
    Vector *list = read_generic_list(&defaultexpr);
    for (int i = 0; i < vec_len(list); i++) {
        void **pair = vec_get(list, i);
        Type *ty = pair[0];
        Node *expr = pair[1];
        if (type_compatible(contexpr->ty, ty))
            return expr;
    }
   if (!defaultexpr)
       errort(tok, "no matching generic selection for %s: %s", node2s(contexpr), ty2s(contexpr->ty));
   return defaultexpr;
}