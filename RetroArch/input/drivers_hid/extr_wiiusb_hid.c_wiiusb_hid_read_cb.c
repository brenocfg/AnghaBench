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
struct TYPE_2__ {int /*<<< orphan*/ * connections; } ;
typedef  TYPE_1__ wiiusb_hid_t ;
struct wiiusb_adapter {size_t slot; int busy; scalar_t__ data; TYPE_1__* hid; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  pad_connection_packet (int /*<<< orphan*/ *,size_t,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int32_t wiiusb_hid_read_cb(int32_t size, void *data)
{
   struct wiiusb_adapter *adapter = (struct wiiusb_adapter*)data;
   wiiusb_hid_t *hid = adapter ? adapter->hid : NULL;

   if (hid && hid->connections && size > 0)
      pad_connection_packet(&hid->connections[adapter->slot],
            adapter->slot, adapter->data-1, size+1);

  if (adapter)
      adapter->busy = false;

  return size;
}