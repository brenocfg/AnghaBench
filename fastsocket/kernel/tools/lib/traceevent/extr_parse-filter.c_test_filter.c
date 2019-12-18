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
struct TYPE_2__ {int value; } ;
struct filter_arg {int type; TYPE_1__ boolean; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
#define  FILTER_ARG_BOOLEAN 134 
#define  FILTER_ARG_EXP 133 
#define  FILTER_ARG_FIELD 132 
#define  FILTER_ARG_NUM 131 
#define  FILTER_ARG_OP 130 
#define  FILTER_ARG_STR 129 
#define  FILTER_ARG_VALUE 128 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  get_arg_value (struct event_format*,struct filter_arg*,struct pevent_record*) ; 
 int test_num (struct event_format*,struct filter_arg*,struct pevent_record*) ; 
 int test_op (struct event_format*,struct filter_arg*,struct pevent_record*) ; 
 int test_str (struct event_format*,struct filter_arg*,struct pevent_record*) ; 

__attribute__((used)) static int test_filter(struct event_format *event,
		       struct filter_arg *arg, struct pevent_record *record)
{
	switch (arg->type) {
	case FILTER_ARG_BOOLEAN:
		/* easy case */
		return arg->boolean.value;

	case FILTER_ARG_OP:
		return test_op(event, arg, record);

	case FILTER_ARG_NUM:
		return test_num(event, arg, record);

	case FILTER_ARG_STR:
		return test_str(event, arg, record);

	case FILTER_ARG_EXP:
	case FILTER_ARG_VALUE:
	case FILTER_ARG_FIELD:
		/*
		 * Expressions, fields and values evaluate
		 * to true if they return non zero
		 */
		return !!get_arg_value(event, arg, record);

	default:
		die("oops!");
		/* ?? */
		return 0;
	}
}