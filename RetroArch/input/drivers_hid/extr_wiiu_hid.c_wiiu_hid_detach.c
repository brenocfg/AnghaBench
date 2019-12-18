#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wiiu_hid_t ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ wiiu_attach_event ;
struct TYPE_6__ {int connected; } ;
typedef  TYPE_2__ wiiu_adapter_t ;

/* Variables and functions */
 TYPE_2__* synchronized_lookup_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wiiu_hid_detach(wiiu_hid_t *hid, wiiu_attach_event *event)
{
   wiiu_adapter_t *adapter = synchronized_lookup_adapter(event->handle);

   /* this will signal the read loop to stop for this adapter
    * the read loop method will update this to ADAPTER_STATE_GC
    * so the adapter poll method can clean it up. */
   if (adapter)
      adapter->connected = false;
}