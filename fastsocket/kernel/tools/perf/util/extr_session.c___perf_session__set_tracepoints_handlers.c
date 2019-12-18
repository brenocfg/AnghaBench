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
struct perf_session {int /*<<< orphan*/  pevent; struct perf_evlist* evlist; } ;
struct perf_evsel_str_handler {int /*<<< orphan*/ * handler; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * func; } ;
struct perf_evsel {TYPE_1__ handler; } ;
struct perf_evlist {int dummy; } ;
struct event_format {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 struct perf_evsel* perf_evlist__find_tracepoint_by_id (struct perf_evlist*,int /*<<< orphan*/ ) ; 
 struct event_format* pevent_find_event_by_name (int /*<<< orphan*/ ,char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

int __perf_session__set_tracepoints_handlers(struct perf_session *session,
					     const struct perf_evsel_str_handler *assocs,
					     size_t nr_assocs)
{
	struct perf_evlist *evlist = session->evlist;
	struct event_format *format;
	struct perf_evsel *evsel;
	char *tracepoint, *name;
	size_t i;
	int err;

	for (i = 0; i < nr_assocs; i++) {
		err = -ENOMEM;
		tracepoint = strdup(assocs[i].name);
		if (tracepoint == NULL)
			goto out;

		err = -ENOENT;
		name = strchr(tracepoint, ':');
		if (name == NULL)
			goto out_free;

		*name++ = '\0';
		format = pevent_find_event_by_name(session->pevent,
						   tracepoint, name);
		if (format == NULL) {
			/*
			 * Adding a handler for an event not in the session,
			 * just ignore it.
			 */
			goto next;
		}

		evsel = perf_evlist__find_tracepoint_by_id(evlist, format->id);
		if (evsel == NULL)
			goto next;

		err = -EEXIST;
		if (evsel->handler.func != NULL)
			goto out_free;
		evsel->handler.func = assocs[i].handler;
next:
		free(tracepoint);
	}

	err = 0;
out:
	return err;

out_free:
	free(tracepoint);
	goto out;
}