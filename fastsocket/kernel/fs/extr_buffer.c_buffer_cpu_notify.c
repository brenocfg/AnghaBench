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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 unsigned long CPU_DEAD ; 
 unsigned long CPU_DEAD_FROZEN ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  buffer_exit_cpu (unsigned long) ; 

__attribute__((used)) static int buffer_cpu_notify(struct notifier_block *self,
			      unsigned long action, void *hcpu)
{
	if (action == CPU_DEAD || action == CPU_DEAD_FROZEN)
		buffer_exit_cpu((unsigned long)hcpu);
	return NOTIFY_OK;
}