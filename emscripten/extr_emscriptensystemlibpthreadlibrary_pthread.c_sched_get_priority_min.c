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
 int SCHED_FIFO ; 
 int SCHED_RR ; 

int sched_get_priority_min(int policy)
{
	// Web workers do not actually support prioritizing threads,
	// but mimic values that Linux apparently reports, see
	// http://man7.org/linux/man-pages/man2/sched_get_priority_min.2.html
	if (policy == SCHED_FIFO || policy == SCHED_RR)
		return 1;
	else
		return 0;
}