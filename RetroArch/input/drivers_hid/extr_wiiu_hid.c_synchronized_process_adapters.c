#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wiiu_hid_t ;
struct TYPE_5__ {int state; struct TYPE_5__* next; } ;
typedef  TYPE_1__ wiiu_adapter_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__* list; } ;

/* Variables and functions */
#define  ADAPTER_STATE_DONE 132 
#define  ADAPTER_STATE_GC 131 
#define  ADAPTER_STATE_NEW 130 
#define  ADAPTER_STATE_READING 129 
#define  ADAPTER_STATE_READY 128 
 int /*<<< orphan*/  OSFastMutex_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSFastMutex_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int) ; 
 TYPE_4__ adapters ; 
 int /*<<< orphan*/  delete_adapter (TYPE_1__*) ; 
 int try_init_driver (TYPE_1__*) ; 

__attribute__((used)) static void synchronized_process_adapters(wiiu_hid_t *hid)
{
   wiiu_adapter_t *adapter = NULL;
   wiiu_adapter_t *prev = NULL, *adapter_next = NULL;
   bool keep_prev = false;

   OSFastMutex_Lock(&(adapters.lock));

   for (adapter = adapters.list; adapter != NULL; adapter = adapter_next)
   {
     adapter_next = adapter->next;

     switch(adapter->state)
     {
       case ADAPTER_STATE_NEW:
          adapter->state = try_init_driver(adapter);
          break;
       case ADAPTER_STATE_READY:
       case ADAPTER_STATE_READING:
       case ADAPTER_STATE_DONE:
          break;
       case ADAPTER_STATE_GC:
          /* remove from the list */
          if (!prev)
             adapters.list = adapter->next;
          else
             prev->next = adapter->next;

          /* adapter is no longer valid after this point */
          delete_adapter(adapter);
          /* signal not to update prev ptr since adapter is now invalid */
          keep_prev = true;
          break;
       default:
          RARCH_ERR("[hid]: Invalid adapter state: %d\n", adapter->state);
          break;
     }
     prev = keep_prev ? prev : adapter;
     keep_prev = false;
   }
   OSFastMutex_Unlock(&(adapters.lock));
}