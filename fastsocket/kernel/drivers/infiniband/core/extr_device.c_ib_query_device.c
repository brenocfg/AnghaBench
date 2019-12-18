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
struct ib_device_attr {int dummy; } ;
struct ib_device {int (* query_device ) (struct ib_device*,struct ib_device_attr*) ;} ;

/* Variables and functions */
 int stub1 (struct ib_device*,struct ib_device_attr*) ; 

int ib_query_device(struct ib_device *device,
		    struct ib_device_attr *device_attr)
{
	return device->query_device(device, device_attr);
}