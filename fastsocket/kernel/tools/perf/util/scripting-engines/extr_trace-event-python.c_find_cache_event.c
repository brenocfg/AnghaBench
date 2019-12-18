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
struct TYPE_4__ {int config; } ;
struct perf_evsel {struct event_format* tp_format; TYPE_2__ attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  args; } ;
struct event_format {char* system; char* name; TYPE_1__ print_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  define_event_symbols (struct event_format*,char*,int /*<<< orphan*/ ) ; 
 struct event_format** events ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static inline struct event_format *find_cache_event(struct perf_evsel *evsel)
{
	static char ev_name[256];
	struct event_format *event;
	int type = evsel->attr.config;

	/*
 	 * XXX: Do we really need to cache this since now we have evsel->tp_format
 	 * cached already? Need to re-read this "cache" routine that as well calls
 	 * define_event_symbols() :-\
 	 */
	if (events[type])
		return events[type];

	events[type] = event = evsel->tp_format;
	if (!event)
		return NULL;

	sprintf(ev_name, "%s__%s", event->system, event->name);

	define_event_symbols(event, ev_name, event->print_fmt.args);

	return event;
}