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
typedef  int uint32_t ;

/* Variables and functions */
 int EPERM ; 
 int KPC_CLASS_POWER_MASK ; 
 int kpc_set_period (int,void*) ; 

__attribute__((used)) static int
sysctl_kpc_set_period(uint32_t classes, void* buf)
{
	/* userspace cannot reconfigure the power class */
	if (classes & KPC_CLASS_POWER_MASK)
		return (EPERM);
	return kpc_set_period( classes, buf);
}