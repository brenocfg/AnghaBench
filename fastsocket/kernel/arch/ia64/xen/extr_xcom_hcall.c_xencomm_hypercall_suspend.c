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
struct sched_shutdown {int /*<<< orphan*/  reason; } ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEDOP_shutdown ; 
 int /*<<< orphan*/  SHUTDOWN_suspend ; 
 int xencomm_arch_hypercall_sched_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xencomm_map_no_alloc (struct sched_shutdown*,int) ; 

int
xencomm_hypercall_suspend(unsigned long srec)
{
	struct sched_shutdown arg;

	arg.reason = SHUTDOWN_suspend;

	return xencomm_arch_hypercall_sched_op(
		SCHEDOP_shutdown, xencomm_map_no_alloc(&arg, sizeof(arg)));
}