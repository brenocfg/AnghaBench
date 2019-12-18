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
 int EAGAIN ; 
 int EINVAL ; 
 int VIOMAJOR_SUBTYPE_SHIFT ; 
 int VIO_MAX_SUBTYPES ; 
 int /*<<< orphan*/ ** vio_handler ; 

int vio_clearHandler(int subtype)
{
	subtype = subtype >> VIOMAJOR_SUBTYPE_SHIFT;
	if ((subtype < 0) || (subtype >= VIO_MAX_SUBTYPES))
		return -EINVAL;
	if (vio_handler[subtype] == NULL)
		return -EAGAIN;
	vio_handler[subtype] = NULL;
	return 0;
}