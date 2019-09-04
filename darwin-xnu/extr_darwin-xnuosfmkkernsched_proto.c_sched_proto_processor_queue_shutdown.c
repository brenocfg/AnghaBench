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
typedef  int /*<<< orphan*/  processor_t ;

/* Variables and functions */

__attribute__((used)) static void
sched_proto_processor_queue_shutdown(
									 processor_t			processor)
{
	/* With a global runqueue, just stop choosing this processor */
	(void)processor;
}