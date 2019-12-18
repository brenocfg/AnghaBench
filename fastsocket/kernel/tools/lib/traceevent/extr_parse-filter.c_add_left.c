#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct filter_arg* left; } ;
struct TYPE_6__ {struct filter_arg* left; } ;
struct TYPE_5__ {struct filter_arg* left; } ;
struct filter_arg {int type; TYPE_1__ num; TYPE_3__ op; TYPE_2__ exp; } ;

/* Variables and functions */
 int const FILTER_ARG_BOOLEAN ; 
#define  FILTER_ARG_EXP 130 
 int const FILTER_ARG_FIELD ; 
#define  FILTER_ARG_NUM 129 
#define  FILTER_ARG_OP 128 
 struct filter_arg* rotate_op_right (struct filter_arg*,struct filter_arg*) ; 

__attribute__((used)) static int add_left(struct filter_arg *op, struct filter_arg *arg)
{
	switch (op->type) {
	case FILTER_ARG_EXP:
		if (arg->type == FILTER_ARG_OP)
			arg = rotate_op_right(arg, op);
		op->exp.left = arg;
		break;

	case FILTER_ARG_OP:
		op->op.left = arg;
		break;
	case FILTER_ARG_NUM:
		if (arg->type == FILTER_ARG_OP)
			arg = rotate_op_right(arg, op);

		/* left arg of compares must be a field */
		if (arg->type != FILTER_ARG_FIELD &&
		    arg->type != FILTER_ARG_BOOLEAN)
			return -1;
		op->num.left = arg;
		break;
	default:
		return -1;
	}
	return 0;
}