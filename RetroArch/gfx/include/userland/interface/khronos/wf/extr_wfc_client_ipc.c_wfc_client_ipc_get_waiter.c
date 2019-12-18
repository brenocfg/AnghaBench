#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ inuse; } ;
typedef  TYPE_2__ WFC_WAITER_T ;
struct TYPE_6__ {TYPE_2__* waiters; int /*<<< orphan*/  sem; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_1__ waitpool; } ;
typedef  TYPE_3__ WFC_CLIENT_IPC_T ;

/* Variables and functions */
 int WFC_CLIENT_IPC_MAX_WAITERS ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_verify (int) ; 

__attribute__((used)) static WFC_WAITER_T *wfc_client_ipc_get_waiter(WFC_CLIENT_IPC_T *client)
{
   int i;
   WFC_WAITER_T *waiter = NULL;

   vcos_semaphore_wait(&client->waitpool.sem);
   vcos_mutex_lock(&client->lock);

   for (i = 0; i < WFC_CLIENT_IPC_MAX_WAITERS; i++)
   {
      if (client->waitpool.waiters[i].inuse == 0)
         break;
   }

   /* If this fails, the semaphore isn't working */
   if (vcos_verify(i != WFC_CLIENT_IPC_MAX_WAITERS))
   {
      waiter = client->waitpool.waiters + i;
      waiter->inuse = 1;
   }
   vcos_mutex_unlock(&client->lock);

   return waiter;
}