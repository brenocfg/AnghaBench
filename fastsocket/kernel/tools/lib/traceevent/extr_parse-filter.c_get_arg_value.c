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
struct pevent_record {int dummy; } ;
struct TYPE_4__ {unsigned long long val; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  field; } ;
struct filter_arg {int type; TYPE_2__ value; TYPE_1__ field; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
#define  FILTER_ARG_EXP 130 
#define  FILTER_ARG_FIELD 129 
#define  FILTER_ARG_VALUE 128 
 int /*<<< orphan*/  FILTER_NUMBER ; 
 int /*<<< orphan*/  die (char*) ; 
 unsigned long long get_exp_value (struct event_format*,struct filter_arg*,struct pevent_record*) ; 
 unsigned long long get_value (struct event_format*,int /*<<< orphan*/ ,struct pevent_record*) ; 

__attribute__((used)) static unsigned long long
get_arg_value(struct event_format *event, struct filter_arg *arg, struct pevent_record *record)
{
	switch (arg->type) {
	case FILTER_ARG_FIELD:
		return get_value(event, arg->field.field, record);

	case FILTER_ARG_VALUE:
		if (arg->value.type != FILTER_NUMBER)
			die("must have number field!");
		return arg->value.val;

	case FILTER_ARG_EXP:
		return get_exp_value(event, arg, record);

	default:
		die("oops in filter");
	}
	return 0;
}