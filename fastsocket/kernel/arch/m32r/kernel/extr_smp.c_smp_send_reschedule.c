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
 int /*<<< orphan*/  RESCHEDULE_IPI ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_is_offline (int) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  send_IPI_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void smp_send_reschedule(int cpu_id)
{
	WARN_ON(cpu_is_offline(cpu_id));
	send_IPI_mask(cpumask_of(cpu_id), RESCHEDULE_IPI, 1);
}