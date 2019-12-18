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
struct pevent {scalar_t__ test_filters; } ;
struct event_list {TYPE_1__* event; struct event_list* next; } ;
struct event_filter {struct pevent* pevent; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int filter_event (struct event_filter*,TYPE_1__*,char const*,char**) ; 
 int find_event (struct pevent*,struct event_list**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_events (struct event_list*) ; 
 char* malloc_or_die (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  pevent_buffer_init (char*,int /*<<< orphan*/ ) ; 
 char* pevent_filter_make_string (struct event_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  show_error (char**,char*,...) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strim (char*) ; 
 int strlen (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 

int pevent_filter_add_filter_str(struct event_filter *filter,
				 const char *filter_str,
				 char **error_str)
{
	struct pevent *pevent = filter->pevent;
	struct event_list *event;
	struct event_list *events = NULL;
	const char *filter_start;
	const char *next_event;
	char *this_event;
	char *event_name = NULL;
	char *sys_name = NULL;
	char *sp;
	int rtn = 0;
	int len;
	int ret;

	/* clear buffer to reset show error */
	pevent_buffer_init("", 0);

	if (error_str)
		*error_str = NULL;

	filter_start = strchr(filter_str, ':');
	if (filter_start)
		len = filter_start - filter_str;
	else
		len = strlen(filter_str);


	do {
		next_event = strchr(filter_str, ',');
		if (next_event &&
		    (!filter_start || next_event < filter_start))
			len = next_event - filter_str;
		else if (filter_start)
			len = filter_start - filter_str;
		else
			len = strlen(filter_str);

		this_event = malloc_or_die(len + 1);
		memcpy(this_event, filter_str, len);
		this_event[len] = 0;

		if (next_event)
			next_event++;

		filter_str = next_event;

		sys_name = strtok_r(this_event, "/", &sp);
		event_name = strtok_r(NULL, "/", &sp);

		if (!sys_name) {
			show_error(error_str, "No filter found");
			/* This can only happen when events is NULL, but still */
			free_events(events);
			free(this_event);
			return -1;
		}

		/* Find this event */
		ret = find_event(pevent, &events, strim(sys_name), strim(event_name));
		if (ret < 0) {
			if (event_name)
				show_error(error_str,
					   "No event found under '%s.%s'",
					   sys_name, event_name);
			else
				show_error(error_str,
					   "No event found under '%s'",
					   sys_name);
			free_events(events);
			free(this_event);
			return -1;
		}
		free(this_event);
	} while (filter_str);

	/* Skip the ':' */
	if (filter_start)
		filter_start++;

	/* filter starts here */
	for (event = events; event; event = event->next) {
		ret = filter_event(filter, event->event, filter_start,
				   error_str);
		/* Failures are returned if a parse error happened */
		if (ret < 0)
			rtn = ret;

		if (ret >= 0 && pevent->test_filters) {
			char *test;
			test = pevent_filter_make_string(filter, event->event->id);
			printf(" '%s: %s'\n", event->event->name, test);
			free(test);
		}
	}

	free_events(events);

	if (rtn >= 0 && pevent->test_filters)
		exit(0);

	return rtn;
}