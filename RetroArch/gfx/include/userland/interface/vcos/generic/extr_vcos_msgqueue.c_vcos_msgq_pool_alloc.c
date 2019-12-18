#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* pool; int /*<<< orphan*/ * waiter; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ VCOS_MSG_T ;
struct TYPE_8__ {int /*<<< orphan*/  waiter; int /*<<< orphan*/  blockpool; int /*<<< orphan*/  sem; } ;
typedef  TYPE_2__ VCOS_MSGQ_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  vcos_assert (TYPE_1__*) ; 
 TYPE_1__* vcos_blockpool_calloc (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_semaphore_trywait (int /*<<< orphan*/ *) ; 

VCOS_MSG_T *vcos_msgq_pool_alloc(VCOS_MSGQ_POOL_T *pool)
{
   VCOS_MSG_T *msg;
   if (vcos_semaphore_trywait(&pool->sem) == VCOS_SUCCESS)
   {
      msg = vcos_blockpool_calloc(&pool->blockpool);
      vcos_assert(msg);
      msg->magic = MAGIC;
      msg->waiter = &pool->waiter;
      msg->pool = pool;
   }
   else
   {
      msg = NULL;
   }
   return msg;
}