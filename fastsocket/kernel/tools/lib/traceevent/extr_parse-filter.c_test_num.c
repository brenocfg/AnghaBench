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
struct filter_arg {TYPE_1__ num; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
#define  FILTER_CMP_EQ 133 
#define  FILTER_CMP_GE 132 
#define  FILTER_CMP_GT 131 
#define  FILTER_CMP_LE 130 
#define  FILTER_CMP_LT 129 
#define  FILTER_CMP_NE 128 
 unsigned long long get_arg_value (struct event_format*,int /*<<< orphan*/ ,struct pevent_record*) ; 

__attribute__((used)) static int test_num(struct event_format *event,
		    struct filter_arg *arg, struct pevent_record *record)
{
	unsigned long long lval, rval;

	lval = get_arg_value(event, arg->num.left, record);
	rval = get_arg_value(event, arg->num.right, record);

	switch (arg->num.type) {
	case FILTER_CMP_EQ:
		return lval == rval;

	case FILTER_CMP_NE:
		return lval != rval;

	case FILTER_CMP_GT:
		return lval > rval;

	case FILTER_CMP_LT:
		return lval < rval;

	case FILTER_CMP_GE:
		return lval >= rval;

	case FILTER_CMP_LE:
		return lval <= rval;

	default:
		/* ?? */
		return 0;
	}
}