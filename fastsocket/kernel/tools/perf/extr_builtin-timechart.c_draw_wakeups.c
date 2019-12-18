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
struct wake_event {int waker; int wakee; scalar_t__ time; struct wake_event* next; } ;
struct per_pidcomm {int Y; scalar_t__ start_time; scalar_t__ end_time; struct per_pidcomm* next; int /*<<< orphan*/  comm; } ;
struct per_pid {int pid; struct per_pid* next; struct per_pidcomm* all; } ;

/* Variables and functions */
 int abs (int) ; 
 struct per_pid* all_data ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_interrupt (scalar_t__,int) ; 
 int /*<<< orphan*/  svg_partial_wakeline (scalar_t__,int,char*,int,char*) ; 
 int /*<<< orphan*/  svg_wakeline (scalar_t__,int,int) ; 
 struct wake_event* wake_events ; 

__attribute__((used)) static void draw_wakeups(void)
{
	struct wake_event *we;
	struct per_pid *p;
	struct per_pidcomm *c;

	we = wake_events;
	while (we) {
		int from = 0, to = 0;
		char *task_from = NULL, *task_to = NULL;

		/* locate the column of the waker and wakee */
		p = all_data;
		while (p) {
			if (p->pid == we->waker || p->pid == we->wakee) {
				c = p->all;
				while (c) {
					if (c->Y && c->start_time <= we->time && c->end_time >= we->time) {
						if (p->pid == we->waker && !from) {
							from = c->Y;
							task_from = strdup(c->comm);
						}
						if (p->pid == we->wakee && !to) {
							to = c->Y;
							task_to = strdup(c->comm);
						}
					}
					c = c->next;
				}
				c = p->all;
				while (c) {
					if (p->pid == we->waker && !from) {
						from = c->Y;
						task_from = strdup(c->comm);
					}
					if (p->pid == we->wakee && !to) {
						to = c->Y;
						task_to = strdup(c->comm);
					}
					c = c->next;
				}
			}
			p = p->next;
		}

		if (!task_from) {
			task_from = malloc(40);
			sprintf(task_from, "[%i]", we->waker);
		}
		if (!task_to) {
			task_to = malloc(40);
			sprintf(task_to, "[%i]", we->wakee);
		}

		if (we->waker == -1)
			svg_interrupt(we->time, to);
		else if (from && to && abs(from - to) == 1)
			svg_wakeline(we->time, from, to);
		else
			svg_partial_wakeline(we->time, from, task_from, to, task_to);
		we = we->next;

		free(task_from);
		free(task_to);
	}
}