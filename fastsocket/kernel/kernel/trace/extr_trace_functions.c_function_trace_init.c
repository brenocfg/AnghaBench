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
struct trace_array {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 struct trace_array* func_trace ; 
 int /*<<< orphan*/  get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  tracing_start_cmdline_record () ; 
 int /*<<< orphan*/  tracing_start_function_trace () ; 

__attribute__((used)) static int function_trace_init(struct trace_array *tr)
{
	func_trace = tr;
	tr->cpu = get_cpu();
	put_cpu();

	tracing_start_cmdline_record();
	tracing_start_function_trace();
	return 0;
}