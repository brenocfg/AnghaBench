#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  operand; TYPE_2__* ty; } ;
struct TYPE_6__ {TYPE_1__* ptr; } ;
struct TYPE_5__ {int size; } ;
typedef  TYPE_3__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  emit (char*,char*,int) ; 
 int /*<<< orphan*/  emit_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_store (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_pre_inc_dec(Node *node, char *op) {
    emit_expr(node->operand);
    emit("%s $%d, #rax", op, node->ty->ptr ? node->ty->ptr->size : 1);
    emit_store(node->operand);
}