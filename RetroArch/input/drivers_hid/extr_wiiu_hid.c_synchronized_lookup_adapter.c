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
struct TYPE_4__ {scalar_t__ handle; struct TYPE_4__* next; } ;
typedef  TYPE_1__ wiiu_adapter_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSFastMutex_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSFastMutex_Unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ adapters ; 

__attribute__((used)) static wiiu_adapter_t *synchronized_lookup_adapter(uint32_t handle)
{
   OSFastMutex_Lock(&(adapters.lock));
   wiiu_adapter_t *iterator;

   for (iterator = adapters.list; iterator != NULL; iterator = iterator->next)
   {
      if (iterator->handle == handle)
         break;
   }
   OSFastMutex_Unlock(&(adapters.lock));

   return iterator;
}