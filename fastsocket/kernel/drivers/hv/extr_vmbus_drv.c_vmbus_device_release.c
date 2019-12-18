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
struct hv_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hv_device* device_to_hv_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct hv_device*) ; 

__attribute__((used)) static void vmbus_device_release(struct device *device)
{
	struct hv_device *hv_dev = device_to_hv_device(device);

	kfree(hv_dev);

}