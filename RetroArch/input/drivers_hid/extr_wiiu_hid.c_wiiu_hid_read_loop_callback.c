#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  driver_handle; TYPE_1__* driver; } ;
typedef  TYPE_2__ wiiu_adapter_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* handle_packet ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ADAPTER_STATE_READING ; 
 scalar_t__ ADAPTER_STATE_READY ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  report_hid_error (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wiiu_hid_read_loop_callback(uint32_t handle, int32_t error,
              uint8_t *buffer, uint32_t buffer_size, void *userdata)
{
   wiiu_adapter_t *adapter = (wiiu_adapter_t *)userdata;
   if (!adapter)
   {
      RARCH_ERR("read_loop_callback: bad userdata\n");
      return;
   }

   if (error < 0)
   {
      report_hid_error("async read failed", adapter, error);
   }

   if (adapter->state == ADAPTER_STATE_READING)
   {
      adapter->state = ADAPTER_STATE_READY;

      if (error == 0)
      {
         adapter->driver->handle_packet(adapter->driver_handle,
            buffer, buffer_size);
      }
   }
}