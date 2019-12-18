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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tracing_stop_cmdline_record () ; 
 int /*<<< orphan*/  unregister_ftrace_graph () ; 

__attribute__((used)) static void graph_trace_reset(struct trace_array *tr)
{
	tracing_stop_cmdline_record();
	unregister_ftrace_graph();
}