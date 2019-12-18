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
struct TYPE_6__ {TYPE_2__* waiters; int /*<<< orphan*/  sem; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_1__ waitpool; } ;
struct TYPE_7__ {scalar_t__ inuse; } ;
typedef  TYPE_2__ MMAL_WAITER_T ;
typedef  TYPE_3__ MMAL_CLIENT_T ;

/* Variables and functions */
 int MAX_WAITERS ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_verify (int) ; 

__attribute__((used)) static MMAL_WAITER_T *get_waiter(MMAL_CLIENT_T *client)
{
   int i;
   MMAL_WAITER_T *waiter = NULL;
   vcos_semaphore_wait(&client->waitpool.sem);
   vcos_mutex_lock(&client->lock);
   for (i=0; i<MAX_WAITERS; i++)
   {
      if (client->waitpool.waiters[i].inuse == 0)
         break;
   }
   /* If this fails, the semaphore is not working */
   if (vcos_verify(i != MAX_WAITERS))
   {
      waiter = client->waitpool.waiters+i;
      waiter->inuse = 1;
   }
   vcos_mutex_unlock(&client->lock);

   return waiter;
}