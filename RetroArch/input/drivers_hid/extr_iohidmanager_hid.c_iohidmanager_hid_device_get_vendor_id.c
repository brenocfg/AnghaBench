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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  IOHIDDeviceRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iohidmanager_hid_device_get_int_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kIOHIDVendorIDKey ; 

__attribute__((used)) static uint16_t iohidmanager_hid_device_get_vendor_id(IOHIDDeviceRef device)
{
   return iohidmanager_hid_device_get_int_property(device,
         CFSTR(kIOHIDVendorIDKey));
}