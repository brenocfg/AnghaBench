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
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_5__ {int /*<<< orphan*/  sem; TYPE_1__* waiters; } ;
struct TYPE_4__ {int /*<<< orphan*/  sem; scalar_t__ inuse; } ;
typedef  TYPE_2__ MMAL_WAITPOOL_T ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
 int MAX_WAITERS ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 char* VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T create_waitpool(MMAL_WAITPOOL_T *waitpool)
{
   VCOS_STATUS_T status;
   int i;

   status = vcos_semaphore_create(&waitpool->sem, VCOS_FUNCTION,
                                  MAX_WAITERS);
   if (status != VCOS_SUCCESS)
      return status==VCOS_SUCCESS ? MMAL_SUCCESS : MMAL_ENOSPC;

   for (i=0; i<MAX_WAITERS; i++)
   {
      waitpool->waiters[i].inuse = 0;
      status = vcos_semaphore_create(&waitpool->waiters[i].sem,
                                     "mmal waiter", 0);
      if (status != VCOS_SUCCESS)
         break;
   }

   if (status != VCOS_SUCCESS)
   {
      /* clean up */
      i--;
      while (i>=0)
      {
         vcos_semaphore_delete(&waitpool->waiters[i].sem);
         i--;
      }
      vcos_semaphore_delete(&waitpool->sem);
   }
   return status==VCOS_SUCCESS ? MMAL_SUCCESS : MMAL_ENOSPC;
}