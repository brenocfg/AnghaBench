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
typedef  TYPE_1__* pthread_mutexattr_t ;
typedef  TYPE_2__* pthread_mutex_t ;
struct TYPE_6__ {int /*<<< orphan*/  handle; int /*<<< orphan*/ * ownerThread; int /*<<< orphan*/  kind; scalar_t__ recursive_count; scalar_t__ lock_idx; } ;
struct TYPE_5__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_DEFAULT ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  pte_osSemaphoreCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int pthread_mutex_init (pthread_mutex_t * mutex, const pthread_mutexattr_t * attr)
{
   int result = 0;
   pthread_mutex_t mx;

   if (mutex == NULL)
      return EINVAL;

   mx = (pthread_mutex_t) calloc (1, sizeof (*mx));

   if (mx == NULL)
      result = ENOMEM;
   else
   {
      mx->lock_idx = 0;
      mx->recursive_count = 0;
      mx->kind = (attr == NULL || *attr == NULL
            ? PTHREAD_MUTEX_DEFAULT : (*attr)->kind);
      mx->ownerThread = NULL;

      pte_osSemaphoreCreate(0,&mx->handle);

   }

   *mutex = mx;

   return (result);
}