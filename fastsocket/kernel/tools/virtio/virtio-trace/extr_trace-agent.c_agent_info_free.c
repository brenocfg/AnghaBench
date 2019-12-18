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
struct agent_info {int cpus; struct agent_info** rw_ti; int /*<<< orphan*/  write_pipe; int /*<<< orphan*/  read_pipe; int /*<<< orphan*/  out_fd; int /*<<< orphan*/  in_fd; int /*<<< orphan*/  ctl_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct agent_info*) ; 

__attribute__((used)) static void agent_info_free(struct agent_info *s)
{
	int i;

	close(s->ctl_fd);
	for (i = 0; i < s->cpus; i++) {
		close(s->rw_ti[i]->in_fd);
		close(s->rw_ti[i]->out_fd);
		close(s->rw_ti[i]->read_pipe);
		close(s->rw_ti[i]->write_pipe);
		free(s->rw_ti[i]);
	}
	free(s);
}