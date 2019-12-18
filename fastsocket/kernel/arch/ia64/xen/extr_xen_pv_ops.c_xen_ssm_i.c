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
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ xen_get_virtual_pend () ; 
 int xen_get_virtual_psr_i () ; 
 int /*<<< orphan*/  xen_hyper_ssm_i () ; 
 int /*<<< orphan*/  xen_set_virtual_psr_i (int) ; 

__attribute__((used)) static void
xen_ssm_i(void)
{
	int old = xen_get_virtual_psr_i();
	xen_set_virtual_psr_i(1);
	barrier();
	if (!old && xen_get_virtual_pend())
		xen_hyper_ssm_i();
}