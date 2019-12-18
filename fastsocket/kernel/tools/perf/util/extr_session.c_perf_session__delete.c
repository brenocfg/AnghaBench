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
struct perf_session {int /*<<< orphan*/  fd; int /*<<< orphan*/  host_machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct perf_session*) ; 
 int /*<<< orphan*/  machine__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_session__delete_dead_threads (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__delete_threads (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__destroy_kernel_maps (struct perf_session*) ; 
 int /*<<< orphan*/  vdso__exit () ; 

void perf_session__delete(struct perf_session *self)
{
	perf_session__destroy_kernel_maps(self);
	perf_session__delete_dead_threads(self);
	perf_session__delete_threads(self);
	machine__exit(&self->host_machine);
	close(self->fd);
	free(self);
	vdso__exit();
}