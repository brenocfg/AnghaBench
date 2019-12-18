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
struct pending_event {struct pending_event* next; } ;

/* Variables and functions */
 struct pending_event* pending_event_avail ; 

__attribute__((used)) static void free_pending_event(struct pending_event *ev)
{
	if (ev != NULL) {
		ev->next = pending_event_avail;
		pending_event_avail = ev;
	}
}