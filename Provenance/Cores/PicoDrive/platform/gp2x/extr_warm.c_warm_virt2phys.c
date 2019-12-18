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
 int /*<<< orphan*/  WARMC_VIRT2PHYS ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  warm_fd ; 

unsigned long warm_virt2phys(const void *ptr)
{
	unsigned long ptrio;
	int ret;

	ptrio = (unsigned long)ptr;
	ret = ioctl(warm_fd, WARMC_VIRT2PHYS, &ptrio);
	if (ret != 0) {
		perror("WARMC_VIRT2PHYS failed");
		return (unsigned long)-1;
	}

	return ptrio;
}