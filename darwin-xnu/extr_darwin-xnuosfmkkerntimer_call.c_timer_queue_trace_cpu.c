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
 int /*<<< orphan*/  timer_call_nosync_cpu (int,void (*) (void*),void*) ; 
 scalar_t__ timer_queue_cpu (int) ; 
 scalar_t__ timer_queue_trace ; 

void
timer_queue_trace_cpu(int ncpu)
{
	timer_call_nosync_cpu(
		ncpu,
		(void(*)(void *))timer_queue_trace,
		(void*) timer_queue_cpu(ncpu));
}