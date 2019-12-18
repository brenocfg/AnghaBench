#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  max_packet_size_tx; int /*<<< orphan*/  max_packet_size_rx; int /*<<< orphan*/  interface_index; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ wiiu_attach_event ;
struct TYPE_7__ {int connected; int /*<<< orphan*/  tx_size; int /*<<< orphan*/  tx_buffer; int /*<<< orphan*/  rx_size; int /*<<< orphan*/  rx_buffer; int /*<<< orphan*/  interface_index; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ wiiu_adapter_t ;

/* Variables and functions */
 TYPE_2__* alloc_zeroed (int,int) ; 
 int /*<<< orphan*/  init_cachealigned_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static wiiu_adapter_t *new_adapter(wiiu_attach_event *event)
{
   wiiu_adapter_t *adapter  = alloc_zeroed(32, sizeof(wiiu_adapter_t));

   if (!adapter)
      return NULL;

   adapter->handle          = event->handle;
   adapter->interface_index = event->interface_index;
   init_cachealigned_buffer(event->max_packet_size_rx, &adapter->rx_buffer, &adapter->rx_size);
   init_cachealigned_buffer(event->max_packet_size_tx, &adapter->tx_buffer, &adapter->tx_size);
   adapter->connected       = true;

   return adapter;
}