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
struct tracer {int (* init ) (struct trace_array*) ;} ;
struct trace_array {int dummy; } ;

/* Variables and functions */
 int stub1 (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_reset_online_cpus (struct trace_array*) ; 

int tracer_init(struct tracer *t, struct trace_array *tr)
{
	tracing_reset_online_cpus(tr);
	return t->init(tr);
}