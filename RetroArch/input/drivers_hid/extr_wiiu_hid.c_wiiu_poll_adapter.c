#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rx_size; int /*<<< orphan*/  rx_buffer; int /*<<< orphan*/  handle; int /*<<< orphan*/  state; int /*<<< orphan*/  connected; } ;
typedef  TYPE_1__ wiiu_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_STATE_DONE ; 
 int /*<<< orphan*/  ADAPTER_STATE_READING ; 
 int /*<<< orphan*/  HIDRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  wiiu_hid_read_loop_callback ; 

__attribute__((used)) static void wiiu_poll_adapter(wiiu_adapter_t *adapter)
{
   if (!adapter->connected)
   {
      adapter->state = ADAPTER_STATE_DONE;
      return;
   }

   adapter->state = ADAPTER_STATE_READING;
   HIDRead(adapter->handle, adapter->rx_buffer, adapter->rx_size,
      wiiu_hid_read_loop_callback, adapter);
}