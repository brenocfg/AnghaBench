#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pevent_record {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct filter_arg {TYPE_1__ exp; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
#define  FILTER_EXP_ADD 138 
#define  FILTER_EXP_AND 137 
#define  FILTER_EXP_DIV 136 
#define  FILTER_EXP_LSHIFT 135 
#define  FILTER_EXP_MOD 134 
#define  FILTER_EXP_MUL 133 
#define  FILTER_EXP_NOT 132 
#define  FILTER_EXP_OR 131 
#define  FILTER_EXP_RSHIFT 130 
#define  FILTER_EXP_SUB 129 
#define  FILTER_EXP_XOR 128 
 int /*<<< orphan*/  die (char*) ; 
 unsigned long long get_arg_value (struct event_format*,int /*<<< orphan*/ ,struct pevent_record*) ; 

__attribute__((used)) static unsigned long long
get_exp_value(struct event_format *event, struct filter_arg *arg, struct pevent_record *record)
{
	unsigned long long lval, rval;

	lval = get_arg_value(event, arg->exp.left, record);
	rval = get_arg_value(event, arg->exp.right, record);

	switch (arg->exp.type) {
	case FILTER_EXP_ADD:
		return lval + rval;

	case FILTER_EXP_SUB:
		return lval - rval;

	case FILTER_EXP_MUL:
		return lval * rval;

	case FILTER_EXP_DIV:
		return lval / rval;

	case FILTER_EXP_MOD:
		return lval % rval;

	case FILTER_EXP_RSHIFT:
		return lval >> rval;

	case FILTER_EXP_LSHIFT:
		return lval << rval;

	case FILTER_EXP_AND:
		return lval & rval;

	case FILTER_EXP_OR:
		return lval | rval;

	case FILTER_EXP_XOR:
		return lval ^ rval;

	case FILTER_EXP_NOT:
	default:
		die("error in exp");
	}
	return 0;
}