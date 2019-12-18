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
struct TYPE_5__ {int /*<<< orphan*/  sem; TYPE_1__* waiters; } ;
typedef  TYPE_2__ WFC_WAITPOOL_T ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_4__ {int /*<<< orphan*/  sem; scalar_t__ inuse; } ;

/* Variables and functions */
 char* VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int WFC_CLIENT_IPC_MAX_WAITERS ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VCOS_STATUS_T wfc_client_ipc_create_waitpool(WFC_WAITPOOL_T *waitpool)
{
   VCOS_STATUS_T status;
   int i;

   status = vcos_semaphore_create(&waitpool->sem, VCOS_FUNCTION,
                                  WFC_CLIENT_IPC_MAX_WAITERS);
   if (status != VCOS_SUCCESS)
      return status;

   for (i = 0; i < WFC_CLIENT_IPC_MAX_WAITERS; i++)
   {
      waitpool->waiters[i].inuse = 0;
      status = vcos_semaphore_create(&waitpool->waiters[i].sem,
                                     "wfc ipc waiter", 0);
      if (status != VCOS_SUCCESS)
         break;
   }

   if (status != VCOS_SUCCESS)
   {
      /* clean up */
      i--;
      while (i >= 0)
      {
         vcos_semaphore_delete(&waitpool->waiters[i].sem);
         i--;
      }
      vcos_semaphore_delete(&waitpool->sem);
   }
   return status;
}