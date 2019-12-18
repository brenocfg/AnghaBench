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
struct TYPE_2__ {int removal_cb; int device_detected; } ;
typedef  TYPE_1__ wiiusb_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CLASS_HID ; 
 int /*<<< orphan*/  USB_DeviceChangeNotifyAsync (int /*<<< orphan*/ ,int (*) (int,void*),void*) ; 

__attribute__((used)) static int wiiusb_hid_change_cb(int result, void *usrdata)
{
   wiiusb_hid_t *hid = (wiiusb_hid_t*)usrdata;

   if (!hid)
      return -1;

   /* As it's not coming from the removal callback
      then we detected a new device being inserted */
  if (!hid->removal_cb)
    hid->device_detected = true;
  else
    hid->removal_cb      = false;

   /* Re-submit the change alert */
   USB_DeviceChangeNotifyAsync(USB_CLASS_HID, wiiusb_hid_change_cb, usrdata);

   return 0;
}