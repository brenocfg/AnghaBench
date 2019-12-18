#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  block_data_size; } ;
typedef  TYPE_2__ VCOS_BLOCKPOOL_T ;
struct TYPE_9__ {scalar_t__ available_blocks; unsigned int num_blocks; int flags; int /*<<< orphan*/ * start; int /*<<< orphan*/ * mem; TYPE_4__* free_list; TYPE_2__* owner; } ;
typedef  TYPE_3__ VCOS_BLOCKPOOL_SUBPOOL_T ;
struct TYPE_7__ {TYPE_4__* next; TYPE_3__* subpool; } ;
struct TYPE_10__ {TYPE_1__ owner; } ;
typedef  TYPE_4__ VCOS_BLOCKPOOL_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_POOL (TYPE_2__*) ; 
 int /*<<< orphan*/  ASSERT_SUBPOOL (TYPE_3__*) ; 
 int /*<<< orphan*/  VCOS_BLOCKPOOL_DEBUG_LOG (char*,void*,...) ; 
 scalar_t__ VCOS_BLOCKPOOL_OVERWRITE_ON_FREE ; 
 int VCOS_BLOCKPOOL_SUBPOOL_FLAG_EXTENSION ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

void vcos_generic_blockpool_free(void *block)
{
   VCOS_BLOCKPOOL_DEBUG_LOG("block %p", block);
   if (block)
   {
      VCOS_BLOCKPOOL_HEADER_T* hdr = (VCOS_BLOCKPOOL_HEADER_T*) block - 1;
      VCOS_BLOCKPOOL_SUBPOOL_T *subpool = hdr->owner.subpool;
      VCOS_BLOCKPOOL_T *pool = NULL;

      ASSERT_SUBPOOL(subpool);
      pool = subpool->owner;
      ASSERT_POOL(pool);

      vcos_mutex_lock(&pool->mutex);
      vcos_assert((unsigned) subpool->available_blocks < subpool->num_blocks);

      /* Change ownership of block to be the free list */
      hdr->owner.next = subpool->free_list;
      subpool->free_list = hdr;
      ++(subpool->available_blocks);

      if (VCOS_BLOCKPOOL_OVERWRITE_ON_FREE)
         memset(block, 0xBD, pool->block_data_size); /* For debugging */

      if ( (subpool->flags & VCOS_BLOCKPOOL_SUBPOOL_FLAG_EXTENSION) &&
            subpool->available_blocks == subpool->num_blocks)
      {
         VCOS_BLOCKPOOL_DEBUG_LOG("%s: freeing subpool %p mem %p", VCOS_FUNCTION,
               subpool, subpool->mem);
         /* Free the sub-pool if it was dynamically allocated */
         vcos_free(subpool->mem);
         subpool->mem = NULL;
         subpool->start = NULL;
      }
      vcos_mutex_unlock(&pool->mutex);
   }
}