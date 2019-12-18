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
struct filter_arg {TYPE_1__ boolean; int /*<<< orphan*/  type; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_ARG_BOOLEAN ; 
 int /*<<< orphan*/  FILTER_FALSE ; 
 struct filter_arg* allocate_arg () ; 
 int /*<<< orphan*/  pevent_buffer_init (char const*,int /*<<< orphan*/ ) ; 
 int process_filter (struct event_format*,struct filter_arg**,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_error (char**,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
process_event(struct event_format *event, const char *filter_str,
	      struct filter_arg **parg, char **error_str)
{
	int ret;

	pevent_buffer_init(filter_str, strlen(filter_str));

	ret = process_filter(event, parg, error_str, 0);
	if (ret == 1) {
		show_error(error_str,
			   "Unbalanced number of ')'");
		return -1;
	}
	if (ret < 0)
		return ret;

	/* If parg is NULL, then make it into FALSE */
	if (!*parg) {
		*parg = allocate_arg();
		(*parg)->type = FILTER_ARG_BOOLEAN;
		(*parg)->boolean.value = FILTER_FALSE;
	}

	return 0;
}