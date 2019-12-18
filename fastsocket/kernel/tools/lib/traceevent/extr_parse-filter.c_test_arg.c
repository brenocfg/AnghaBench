#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct filter_arg* left; int /*<<< orphan*/  type; struct filter_arg* right; } ;
struct TYPE_7__ {struct filter_arg* right; struct filter_arg* left; } ;
struct TYPE_6__ {struct filter_arg* right; struct filter_arg* left; } ;
struct TYPE_5__ {int value; } ;
struct filter_arg {int type; TYPE_4__ op; TYPE_3__ num; TYPE_2__ exp; TYPE_1__ boolean; } ;
typedef  enum filter_vals { ____Placeholder_filter_vals } filter_vals ;

/* Variables and functions */
#define  FILTER_ARG_BOOLEAN 137 
#define  FILTER_ARG_EXP 136 
#define  FILTER_ARG_FIELD 135 
#define  FILTER_ARG_NUM 134 
#define  FILTER_ARG_OP 133 
#define  FILTER_ARG_STR 132 
#define  FILTER_ARG_VALUE 131 
 int /*<<< orphan*/  FILTER_OP_AND ; 
 int /*<<< orphan*/  FILTER_OP_NOT ; 
 int /*<<< orphan*/  FILTER_OP_OR ; 
#define  FILTER_VAL_FALSE 130 
#define  FILTER_VAL_NORM 129 
#define  FILTER_VAL_TRUE 128 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  reparent_op_arg (struct filter_arg*,struct filter_arg*,struct filter_arg*) ; 

enum filter_vals test_arg(struct filter_arg *parent, struct filter_arg *arg)
{
	enum filter_vals lval, rval;

	switch (arg->type) {

		/* bad case */
	case FILTER_ARG_BOOLEAN:
		return FILTER_VAL_FALSE + arg->boolean.value;

		/* good cases: */
	case FILTER_ARG_STR:
	case FILTER_ARG_VALUE:
	case FILTER_ARG_FIELD:
		return FILTER_VAL_NORM;

	case FILTER_ARG_EXP:
		lval = test_arg(arg, arg->exp.left);
		if (lval != FILTER_VAL_NORM)
			return lval;
		rval = test_arg(arg, arg->exp.right);
		if (rval != FILTER_VAL_NORM)
			return rval;
		return FILTER_VAL_NORM;

	case FILTER_ARG_NUM:
		lval = test_arg(arg, arg->num.left);
		if (lval != FILTER_VAL_NORM)
			return lval;
		rval = test_arg(arg, arg->num.right);
		if (rval != FILTER_VAL_NORM)
			return rval;
		return FILTER_VAL_NORM;

	case FILTER_ARG_OP:
		if (arg->op.type != FILTER_OP_NOT) {
			lval = test_arg(arg, arg->op.left);
			switch (lval) {
			case FILTER_VAL_NORM:
				break;
			case FILTER_VAL_TRUE:
				if (arg->op.type == FILTER_OP_OR)
					return FILTER_VAL_TRUE;
				rval = test_arg(arg, arg->op.right);
				if (rval != FILTER_VAL_NORM)
					return rval;

				reparent_op_arg(parent, arg, arg->op.right);
				return FILTER_VAL_NORM;

			case FILTER_VAL_FALSE:
				if (arg->op.type == FILTER_OP_AND)
					return FILTER_VAL_FALSE;
				rval = test_arg(arg, arg->op.right);
				if (rval != FILTER_VAL_NORM)
					return rval;

				reparent_op_arg(parent, arg, arg->op.right);
				return FILTER_VAL_NORM;
			}
		}

		rval = test_arg(arg, arg->op.right);
		switch (rval) {
		case FILTER_VAL_NORM:
			break;
		case FILTER_VAL_TRUE:
			if (arg->op.type == FILTER_OP_OR)
				return FILTER_VAL_TRUE;
			if (arg->op.type == FILTER_OP_NOT)
				return FILTER_VAL_FALSE;

			reparent_op_arg(parent, arg, arg->op.left);
			return FILTER_VAL_NORM;

		case FILTER_VAL_FALSE:
			if (arg->op.type == FILTER_OP_AND)
				return FILTER_VAL_FALSE;
			if (arg->op.type == FILTER_OP_NOT)
				return FILTER_VAL_TRUE;

			reparent_op_arg(parent, arg, arg->op.left);
			return FILTER_VAL_NORM;
		}

		return FILTER_VAL_NORM;
	default:
		die("bad arg in filter tree");
	}
	return FILTER_VAL_NORM;
}