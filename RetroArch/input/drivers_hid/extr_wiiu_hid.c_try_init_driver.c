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
struct TYPE_6__ {TYPE_1__* driver; int /*<<< orphan*/ * driver_handle; } ;
typedef  TYPE_2__ wiiu_adapter_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * (* init ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_STATE_DONE ; 
 int /*<<< orphan*/  ADAPTER_STATE_READY ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*) ; 

__attribute__((used)) static uint8_t try_init_driver(wiiu_adapter_t *adapter)
{
   adapter->driver_handle = adapter->driver->init(adapter);
   if (adapter->driver_handle == NULL)
   {
     RARCH_ERR("[hid]: Failed to initialize driver: %s\n",
        adapter->driver->name);
     return ADAPTER_STATE_DONE;
   }

   return ADAPTER_STATE_READY;
}