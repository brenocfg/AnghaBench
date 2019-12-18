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
struct TYPE_6__ {TYPE_1__* driver; int /*<<< orphan*/ * driver_handle; struct TYPE_6__* tx_buffer; struct TYPE_6__* rx_buffer; } ;
typedef  TYPE_2__ wiiu_adapter_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_adapter(wiiu_adapter_t *adapter)
{
   if (!adapter)
      return;

   if (adapter->rx_buffer)
   {
      free(adapter->rx_buffer);
      adapter->rx_buffer = NULL;
   }
   if (adapter->tx_buffer)
   {
      free(adapter->tx_buffer);
      adapter->tx_buffer = NULL;
   }
   if (adapter->driver && adapter->driver_handle) {
      adapter->driver->free(adapter->driver_handle);
      adapter->driver_handle = NULL;
      adapter->driver = NULL;
   }

   free(adapter);
}