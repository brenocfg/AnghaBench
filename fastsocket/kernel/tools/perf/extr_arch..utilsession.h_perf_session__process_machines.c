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
struct perf_tool {int dummy; } ;
struct perf_session {int /*<<< orphan*/  machines; int /*<<< orphan*/  host_machine; } ;
typedef  int /*<<< orphan*/  (* machine__process_t ) (int /*<<< orphan*/ *,struct perf_tool*) ;

/* Variables and functions */
 void machines__process (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,struct perf_tool*),struct perf_tool*) ; 

__attribute__((used)) static inline
void perf_session__process_machines(struct perf_session *self,
				    struct perf_tool *tool,
				    machine__process_t process)
{
	process(&self->host_machine, tool);
	return machines__process(&self->machines, process, tool);
}