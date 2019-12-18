#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/ * lvarinit; TYPE_1__* ty; int /*<<< orphan*/  loff; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 scalar_t__ AST_LVAR ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_decl_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ensure_lvar_init(Node *node) {
    SAVE;
    assert(node->kind == AST_LVAR);
    if (node->lvarinit)
        emit_decl_init(node->lvarinit, node->loff, node->ty->size);
    node->lvarinit = NULL;
}