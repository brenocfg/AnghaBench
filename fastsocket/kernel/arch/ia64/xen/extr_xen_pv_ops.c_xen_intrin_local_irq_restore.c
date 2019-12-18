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
 unsigned long IA64_PSR_I ; 
 int /*<<< orphan*/  xen_rsm_i () ; 
 int /*<<< orphan*/  xen_ssm_i () ; 

__attribute__((used)) static void
xen_intrin_local_irq_restore(unsigned long mask)
{
	if (mask & IA64_PSR_I)
		xen_ssm_i();
	else
		xen_rsm_i();
}