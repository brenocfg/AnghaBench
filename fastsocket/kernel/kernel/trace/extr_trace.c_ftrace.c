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
struct trace_array_cpu {int /*<<< orphan*/  disabled; } ;
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  trace_function (struct trace_array*,unsigned long,unsigned long,unsigned long,int) ; 

void
ftrace(struct trace_array *tr, struct trace_array_cpu *data,
       unsigned long ip, unsigned long parent_ip, unsigned long flags,
       int pc)
{
	if (likely(!atomic_read(&data->disabled)))
		trace_function(tr, ip, parent_ip, flags, pc);
}