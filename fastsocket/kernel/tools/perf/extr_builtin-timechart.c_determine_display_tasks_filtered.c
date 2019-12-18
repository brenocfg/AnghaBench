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
struct per_pidcomm {int display; int start_time; scalar_t__ end_time; struct per_pidcomm* next; } ;
struct per_pid {int display; int start_time; scalar_t__ end_time; struct per_pid* next; struct per_pidcomm* all; } ;

/* Variables and functions */
 struct per_pid* all_data ; 
 void* first_time ; 
 void* last_time ; 
 scalar_t__ passes_filter (struct per_pid*,struct per_pidcomm*) ; 

__attribute__((used)) static int determine_display_tasks_filtered(void)
{
	struct per_pid *p;
	struct per_pidcomm *c;
	int count = 0;

	p = all_data;
	while (p) {
		p->display = 0;
		if (p->start_time == 1)
			p->start_time = first_time;

		/* no exit marker, task kept running to the end */
		if (p->end_time == 0)
			p->end_time = last_time;

		c = p->all;

		while (c) {
			c->display = 0;

			if (c->start_time == 1)
				c->start_time = first_time;

			if (passes_filter(p, c)) {
				c->display = 1;
				p->display = 1;
				count++;
			}

			if (c->end_time == 0)
				c->end_time = last_time;

			c = c->next;
		}
		p = p->next;
	}
	return count;
}