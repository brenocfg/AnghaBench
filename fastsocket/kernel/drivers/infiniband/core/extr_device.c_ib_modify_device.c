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
struct ib_device_modify {int dummy; } ;
struct ib_device {int (* modify_device ) (struct ib_device*,int,struct ib_device_modify*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct ib_device*,int,struct ib_device_modify*) ; 

int ib_modify_device(struct ib_device *device,
		     int device_modify_mask,
		     struct ib_device_modify *device_modify)
{
	if (!device->modify_device)
		return -ENOSYS;

	return device->modify_device(device, device_modify_mask,
				     device_modify);
}