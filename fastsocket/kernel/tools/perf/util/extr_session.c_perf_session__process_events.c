#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_tool {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data_offset; } ;
struct perf_session {int /*<<< orphan*/  size; TYPE_1__ header; int /*<<< orphan*/  fd_pipe; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __perf_session__process_events (struct perf_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_tool*) ; 
 int __perf_session__process_pipe_events (struct perf_session*,struct perf_tool*) ; 
 int /*<<< orphan*/ * perf_session__register_idle_thread (struct perf_session*) ; 

int perf_session__process_events(struct perf_session *self,
				 struct perf_tool *tool)
{
	int err;

	if (perf_session__register_idle_thread(self) == NULL)
		return -ENOMEM;

	if (!self->fd_pipe)
		err = __perf_session__process_events(self,
						     self->header.data_offset,
						     self->header.data_size,
						     self->size, tool);
	else
		err = __perf_session__process_pipe_events(self, tool);

	return err;
}