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
typedef  int /*<<< orphan*/  iohidmanager_hid_t ;
typedef  int /*<<< orphan*/  IOReturn ;
typedef  int /*<<< orphan*/  IOHIDDeviceRef ;

/* Variables and functions */
 scalar_t__ hid_driver_get_data () ; 
 int /*<<< orphan*/  iohidmanager_hid_device_add_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iohidmanager_hid_device_add(void *data, IOReturn result,
   void* sender, IOHIDDeviceRef device)
{
	iohidmanager_hid_t *hid = (iohidmanager_hid_t*)	hid_driver_get_data();
	iohidmanager_hid_device_add_device(device, hid);
}