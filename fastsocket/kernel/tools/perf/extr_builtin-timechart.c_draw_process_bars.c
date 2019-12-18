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
struct per_pidcomm {int Y; char* comm; int total_time; struct per_pidcomm* next; int /*<<< orphan*/  start_time; struct cpu_sample* samples; int /*<<< orphan*/  end_time; int /*<<< orphan*/  display; } ;
struct per_pid {int pid; struct per_pid* next; struct per_pidcomm* all; } ;
struct cpu_sample {scalar_t__ type; struct cpu_sample* next; int /*<<< orphan*/  end_time; int /*<<< orphan*/  start_time; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 scalar_t__ TYPE_BLOCKED ; 
 scalar_t__ TYPE_RUNNING ; 
 scalar_t__ TYPE_WAITING ; 
 struct per_pid* all_data ; 
 int numcpus ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,double) ; 
 int /*<<< orphan*/  svg_box (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svg_sample (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_text (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svg_waiting (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_process_bars(void)
{
	struct per_pid *p;
	struct per_pidcomm *c;
	struct cpu_sample *sample;
	int Y = 0;

	Y = 2 * numcpus + 2;

	p = all_data;
	while (p) {
		c = p->all;
		while (c) {
			if (!c->display) {
				c->Y = 0;
				c = c->next;
				continue;
			}

			svg_box(Y, c->start_time, c->end_time, "process");
			sample = c->samples;
			while (sample) {
				if (sample->type == TYPE_RUNNING)
					svg_sample(Y, sample->cpu, sample->start_time, sample->end_time);
				if (sample->type == TYPE_BLOCKED)
					svg_box(Y, sample->start_time, sample->end_time, "blocked");
				if (sample->type == TYPE_WAITING)
					svg_waiting(Y, sample->start_time, sample->end_time);
				sample = sample->next;
			}

			if (c->comm) {
				char comm[256];
				if (c->total_time > 5000000000) /* 5 seconds */
					sprintf(comm, "%s:%i (%2.2fs)", c->comm, p->pid, c->total_time / 1000000000.0);
				else
					sprintf(comm, "%s:%i (%3.1fms)", c->comm, p->pid, c->total_time / 1000000.0);

				svg_text(Y, c->start_time, comm);
			}
			c->Y = Y;
			Y++;
			c = c->next;
		}
		p = p->next;
	}
}