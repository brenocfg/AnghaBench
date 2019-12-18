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
typedef  int /*<<< orphan*/  uint8_t ;
struct iohidmanager_hid_adapter {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOHIDDeviceSetReport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kIOHIDReportTypeOutput ; 

__attribute__((used)) static void iohidmanager_hid_device_send_control(void *data,
      uint8_t* data_buf, size_t size)
{
   struct iohidmanager_hid_adapter *adapter =
      (struct iohidmanager_hid_adapter*)data;

   if (adapter)
      IOHIDDeviceSetReport(adapter->handle,
            kIOHIDReportTypeOutput, 0x01, data_buf + 1, size - 1);
}