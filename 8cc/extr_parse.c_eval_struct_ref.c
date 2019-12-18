#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kind; TYPE_1__* ty; struct TYPE_6__* struc; } ;
struct TYPE_5__ {int offset; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 scalar_t__ AST_STRUCT_REF ; 
 int eval_intexpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eval_struct_ref(Node *node, int offset) {
    if (node->kind == AST_STRUCT_REF)
        return eval_struct_ref(node->struc, node->ty->offset + offset);
    return eval_intexpr(node, NULL) + offset;
}