#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pevent {int nr_events; struct event_format** events; } ;
struct event_list {int dummy; } ;
struct event_format {int dummy; } ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int REG_ICASE ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  add_event (struct event_list**,struct event_format*) ; 
 scalar_t__ event_match (struct event_format*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc_or_die (scalar_t__) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
find_event(struct pevent *pevent, struct event_list **events,
	   char *sys_name, char *event_name)
{
	struct event_format *event;
	regex_t ereg;
	regex_t sreg;
	int match = 0;
	char *reg;
	int ret;
	int i;

	if (!event_name) {
		/* if no name is given, then swap sys and name */
		event_name = sys_name;
		sys_name = NULL;
	}

	reg = malloc_or_die(strlen(event_name) + 3);
	sprintf(reg, "^%s$", event_name);

	ret = regcomp(&ereg, reg, REG_ICASE|REG_NOSUB);
	free(reg);

	if (ret)
		return -1;

	if (sys_name) {
		reg = malloc_or_die(strlen(sys_name) + 3);
		sprintf(reg, "^%s$", sys_name);
		ret = regcomp(&sreg, reg, REG_ICASE|REG_NOSUB);
		free(reg);
		if (ret) {
			regfree(&ereg);
			return -1;
		}
	}

	for (i = 0; i < pevent->nr_events; i++) {
		event = pevent->events[i];
		if (event_match(event, sys_name ? &sreg : NULL, &ereg)) {
			match = 1;
			add_event(events, event);
		}
	}

	regfree(&ereg);
	if (sys_name)
		regfree(&sreg);

	if (!match)
		return -1;

	return 0;
}