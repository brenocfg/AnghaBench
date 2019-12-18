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
typedef  int /*<<< orphan*/  VCOS_MSG_T ;
struct TYPE_4__ {int /*<<< orphan*/  on_reply; } ;
struct TYPE_5__ {int /*<<< orphan*/  blockpool; int /*<<< orphan*/  magic; TYPE_1__ waiter; int /*<<< orphan*/  sem; } ;
typedef  TYPE_2__ VCOS_MSGQ_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC ; 
 int /*<<< orphan*/  VCOS_BLOCKPOOL_ALIGN_DEFAULT ; 
 scalar_t__ VCOS_SUCCESS ; 
 scalar_t__ vcos_blockpool_create_on_heap (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vcos_blockpool_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_msgq_pool_on_reply ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char const*,size_t) ; 

VCOS_STATUS_T vcos_msgq_pool_create(VCOS_MSGQ_POOL_T *pool,
                                    size_t count,
                                    size_t payload_size,
                                    const char *name)
{
   VCOS_STATUS_T status;
   int bp_size = payload_size + sizeof(VCOS_MSG_T);
   status = vcos_blockpool_create_on_heap(&pool->blockpool,
                                          count, bp_size,
                                          VCOS_BLOCKPOOL_ALIGN_DEFAULT,
                                          0,
                                          name);
   if (status != VCOS_SUCCESS)
      goto fail_pool;

   status = vcos_semaphore_create(&pool->sem, name, count);
   if (status != VCOS_SUCCESS)
      goto fail_sem;

   pool->waiter.on_reply = vcos_msgq_pool_on_reply;
   pool->magic = MAGIC;
   return status;

fail_sem:
   vcos_blockpool_delete(&pool->blockpool);
fail_pool:
   return status;
}