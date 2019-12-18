#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct iohidmanager_hid_adapter {size_t slot; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * slots; } ;
typedef  TYPE_1__ iohidmanager_hid_t ;
typedef  int /*<<< orphan*/  IOReturn ;
typedef  int /*<<< orphan*/  IOHIDReportType ;
typedef  scalar_t__ CFIndex ;

/* Variables and functions */
 scalar_t__ hid_driver_get_data () ; 
 int /*<<< orphan*/  pad_connection_packet (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iohidmanager_hid_device_report(void *data,
      IOReturn result, void *sender,
      IOHIDReportType type, uint32_t reportID, uint8_t *report,
      CFIndex reportLength)
{
   struct iohidmanager_hid_adapter *adapter =
      (struct iohidmanager_hid_adapter*)data;
   iohidmanager_hid_t *hid = (iohidmanager_hid_t*)hid_driver_get_data();

   if (hid && adapter)
      pad_connection_packet(&hid->slots[adapter->slot], adapter->slot,
            adapter->data, (uint32_t)(reportLength + 1));
}