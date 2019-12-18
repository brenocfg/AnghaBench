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

/* Variables and functions */
 int /*<<< orphan*/  __start___tracepoints ; 
 int /*<<< orphan*/  __stop___tracepoints ; 
 int /*<<< orphan*/  module_update_tracepoints () ; 
 int /*<<< orphan*/  tracepoint_update_probe_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tracepoint_update_probes(void)
{
	/* Core kernel tracepoints */
	tracepoint_update_probe_range(__start___tracepoints,
		__stop___tracepoints);
	/* tracepoints in modules. */
	module_update_tracepoints();
}