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
struct TYPE_3__ {int /*<<< orphan*/ * connections; } ;
typedef  TYPE_1__ wiiusb_hid_t ;
struct wiiusb_adapter {size_t slot; struct wiiusb_adapter* data; struct wiiusb_adapter* send_control_buffer; TYPE_1__* hid; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct wiiusb_adapter*) ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (size_t,char const*) ; 
 int /*<<< orphan*/  pad_connection_pad_deinit (int /*<<< orphan*/ *,size_t) ; 
 char* wiiusb_hid_joypad_name (TYPE_1__*,size_t) ; 

__attribute__((used)) static int32_t wiiusb_hid_release_adapter(struct wiiusb_adapter *adapter)
{
   wiiusb_hid_t *hid = NULL;
   const char *name  = NULL;

   if (!adapter)
      return -1;

   hid  = adapter->hid;
   name = wiiusb_hid_joypad_name(hid, adapter->slot);

   input_autoconfigure_disconnect(adapter->slot, name);

   pad_connection_pad_deinit(&hid->connections[adapter->slot], adapter->slot);

   free(adapter->send_control_buffer);
   free(adapter->data);
   free(adapter);

   return 0;
}