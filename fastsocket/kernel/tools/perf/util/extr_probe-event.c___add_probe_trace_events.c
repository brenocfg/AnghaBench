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
struct strlist {int dummy; } ;
struct TYPE_4__ {char* symbol; } ;
struct probe_trace_event {char* event; char* group; TYPE_2__ point; } ;
struct TYPE_3__ {char* function; } ;
struct perf_probe_event {char* event; char* group; TYPE_1__ point; scalar_t__ uprobes; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 char* PERFPROBE_GROUP ; 
 int /*<<< orphan*/  close (int) ; 
 int get_new_event_name (char*,int,char const*,struct strlist*,int) ; 
 struct strlist* get_probe_trace_event_names (int,int) ; 
 int open_kprobe_events (int) ; 
 int open_uprobe_events (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_perf_probe_event (struct perf_probe_event*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strlist__add (struct strlist*,char const*) ; 
 int /*<<< orphan*/  strlist__delete (struct strlist*) ; 
 int write_probe_trace_event (int,struct probe_trace_event*) ; 

__attribute__((used)) static int __add_probe_trace_events(struct perf_probe_event *pev,
				     struct probe_trace_event *tevs,
				     int ntevs, bool allow_suffix)
{
	int i, fd, ret;
	struct probe_trace_event *tev = NULL;
	char buf[64];
	const char *event, *group;
	struct strlist *namelist;

	if (pev->uprobes)
		fd = open_uprobe_events(true);
	else
		fd = open_kprobe_events(true);

	if (fd < 0)
		return fd;
	/* Get current event names */
	namelist = get_probe_trace_event_names(fd, false);
	if (!namelist) {
		pr_debug("Failed to get current event list.\n");
		return -EIO;
	}

	ret = 0;
	printf("Added new event%s\n", (ntevs > 1) ? "s:" : ":");
	for (i = 0; i < ntevs; i++) {
		tev = &tevs[i];
		if (pev->event)
			event = pev->event;
		else
			if (pev->point.function)
				event = pev->point.function;
			else
				event = tev->point.symbol;
		if (pev->group)
			group = pev->group;
		else
			group = PERFPROBE_GROUP;

		/* Get an unused new event name */
		ret = get_new_event_name(buf, 64, event,
					 namelist, allow_suffix);
		if (ret < 0)
			break;
		event = buf;

		tev->event = strdup(event);
		tev->group = strdup(group);
		if (tev->event == NULL || tev->group == NULL) {
			ret = -ENOMEM;
			break;
		}
		ret = write_probe_trace_event(fd, tev);
		if (ret < 0)
			break;
		/* Add added event name to namelist */
		strlist__add(namelist, event);

		/* Trick here - save current event/group */
		event = pev->event;
		group = pev->group;
		pev->event = tev->event;
		pev->group = tev->group;
		show_perf_probe_event(pev);
		/* Trick here - restore current event/group */
		pev->event = (char *)event;
		pev->group = (char *)group;

		/*
		 * Probes after the first probe which comes from same
		 * user input are always allowed to add suffix, because
		 * there might be several addresses corresponding to
		 * one code line.
		 */
		allow_suffix = true;
	}

	if (ret >= 0) {
		/* Show how to use the event. */
		printf("\nYou can now use it in all perf tools, such as:\n\n");
		printf("\tperf record -e %s:%s -aR sleep 1\n\n", tev->group,
			 tev->event);
	}

	strlist__delete(namelist);
	close(fd);
	return ret;
}