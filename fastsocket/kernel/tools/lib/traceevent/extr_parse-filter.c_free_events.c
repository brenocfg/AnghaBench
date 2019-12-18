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
struct event_list {struct event_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct event_list*) ; 

__attribute__((used)) static void free_events(struct event_list *events)
{
	struct event_list *event;

	while (events) {
		event = events;
		events = events->next;
		free(event);
	}
}