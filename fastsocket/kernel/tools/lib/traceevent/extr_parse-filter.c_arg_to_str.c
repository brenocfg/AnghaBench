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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct filter_arg {int type; TYPE_1__ boolean; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
#define  FILTER_ARG_BOOLEAN 134 
#define  FILTER_ARG_EXP 133 
#define  FILTER_ARG_FIELD 132 
#define  FILTER_ARG_NUM 131 
#define  FILTER_ARG_OP 130 
#define  FILTER_ARG_STR 129 
#define  FILTER_ARG_VALUE 128 
 char* exp_to_str (struct event_filter*,struct filter_arg*) ; 
 char* field_to_str (struct event_filter*,struct filter_arg*) ; 
 char* malloc_or_die (int) ; 
 char* num_to_str (struct event_filter*,struct filter_arg*) ; 
 char* op_to_str (struct event_filter*,struct filter_arg*) ; 
 char* str_to_str (struct event_filter*,struct filter_arg*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* val_to_str (struct event_filter*,struct filter_arg*) ; 

__attribute__((used)) static char *arg_to_str(struct event_filter *filter, struct filter_arg *arg)
{
	char *str;

	switch (arg->type) {
	case FILTER_ARG_BOOLEAN:
		str = malloc_or_die(6);
		if (arg->boolean.value)
			strcpy(str, "TRUE");
		else
			strcpy(str, "FALSE");
		return str;

	case FILTER_ARG_OP:
		return op_to_str(filter, arg);

	case FILTER_ARG_NUM:
		return num_to_str(filter, arg);

	case FILTER_ARG_STR:
		return str_to_str(filter, arg);

	case FILTER_ARG_VALUE:
		return val_to_str(filter, arg);

	case FILTER_ARG_FIELD:
		return field_to_str(filter, arg);

	case FILTER_ARG_EXP:
		return exp_to_str(filter, arg);

	default:
		/* ?? */
		return NULL;
	}

}