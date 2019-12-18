#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wiiu_hid_t ;
struct TYPE_4__ {scalar_t__ state; struct TYPE_4__* next; } ;
typedef  TYPE_1__ wiiu_adapter_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__* list; } ;

/* Variables and functions */
 scalar_t__ ADAPTER_STATE_DONE ; 
 scalar_t__ ADAPTER_STATE_GC ; 
 scalar_t__ ADAPTER_STATE_READY ; 
 int /*<<< orphan*/  OSFastMutex_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSFastMutex_Unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ adapters ; 
 int /*<<< orphan*/  wiiu_poll_adapter (TYPE_1__*) ; 

__attribute__((used)) static void wiiu_poll_adapters(wiiu_hid_t *hid)
{
   wiiu_adapter_t *it;
   OSFastMutex_Lock(&(adapters.lock));

   for (it = adapters.list; it != NULL; it = it->next)
   {
      if (it->state == ADAPTER_STATE_READY)
         wiiu_poll_adapter(it);

      if (it->state == ADAPTER_STATE_DONE)
         it->state = ADAPTER_STATE_GC;
   }

   OSFastMutex_Unlock(&(adapters.lock));
}