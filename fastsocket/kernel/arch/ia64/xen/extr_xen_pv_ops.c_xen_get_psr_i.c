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
 scalar_t__ xen_get_virtual_psr_i () ; 

__attribute__((used)) static unsigned long
xen_get_psr_i(void)
{
	return xen_get_virtual_psr_i() ? IA64_PSR_I : 0;
}