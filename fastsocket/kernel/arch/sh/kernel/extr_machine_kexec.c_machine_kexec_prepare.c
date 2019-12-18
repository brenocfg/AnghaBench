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
struct kimage {scalar_t__ start; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PHYSADDR (scalar_t__) ; 

int machine_kexec_prepare(struct kimage *image)
{
	/* older versions of kexec-tools are passing
	 * the zImage entry point as a virtual address.
	 */
	if (image->start != PHYSADDR(image->start))
		return -EINVAL; /* upgrade your kexec-tools */

	return 0;
}