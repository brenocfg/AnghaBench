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
struct TYPE_2__ {int removal_cb; struct wiiusb_adapter* adapters_head; scalar_t__ manual_removal; } ;
typedef  TYPE_1__ wiiusb_hid_t ;
struct wiiusb_adapter {struct wiiusb_adapter* next; TYPE_1__* hid; } ;

/* Variables and functions */
 int /*<<< orphan*/  wiiusb_hid_release_adapter (struct wiiusb_adapter*) ; 

__attribute__((used)) static int wiiusb_hid_removal_cb(int result, void *usrdata)
{
   struct wiiusb_adapter *adapter = (struct wiiusb_adapter *)usrdata;
   wiiusb_hid_t *hid              = adapter ? adapter->hid       : NULL;
   struct wiiusb_adapter *temp    = hid     ? hid->adapters_head : NULL;

   if (!adapter || !hid || !temp || hid->manual_removal)
      return -1;

   if (temp == adapter)
      hid->adapters_head = adapter->next;
   else
      while (temp->next)
      {
         if (temp->next == adapter)
         {
            temp->next = adapter->next;
            break;
         }
         temp = temp->next;
      }

   /* get rid of the adapter */
   wiiusb_hid_release_adapter(adapter);

   /* notify that we pass thru the removal callback */
   hid->removal_cb = true;

   return 0;
}