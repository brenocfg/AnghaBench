#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int prio; int /*<<< orphan*/  op; TYPE_1__* left; } ;
struct print_arg {TYPE_2__ op; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PRINT_NULL ; 
 int get_op_prio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_op_prio(struct print_arg *arg)
{

	/* single ops are the greatest */
	if (!arg->op.left || arg->op.left->type == PRINT_NULL)
		arg->op.prio = 0;
	else
		arg->op.prio = get_op_prio(arg->op.op);

	return arg->op.prio;
}