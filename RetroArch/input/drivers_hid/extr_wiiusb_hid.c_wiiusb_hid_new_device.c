#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct wiiusb_adapter* adapters_head; } ;
typedef  TYPE_1__ wiiusb_hid_t ;
struct wiiusb_adapter {scalar_t__ device_id; struct wiiusb_adapter* next; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static bool wiiusb_hid_new_device(wiiusb_hid_t *hid, int32_t id)
{
   struct wiiusb_adapter *temp;

   if (!hid)
      return false; /* false, so we do not proceed to add it */

   temp = hid->adapters_head;
   while (temp)
   {
      if (temp->device_id == id)
         return false;

      temp = temp->next;
   }

   return true;
}