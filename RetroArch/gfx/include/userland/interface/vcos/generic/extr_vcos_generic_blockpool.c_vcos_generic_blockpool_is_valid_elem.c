#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t VCOS_UNSIGNED ;
struct TYPE_9__ {size_t num_subpools; int block_size; int /*<<< orphan*/  mutex; TYPE_3__* subpools; } ;
typedef  TYPE_2__ VCOS_BLOCKPOOL_T ;
struct TYPE_10__ {int num_blocks; TYPE_2__* owner; scalar_t__ start; scalar_t__ mem; } ;
typedef  TYPE_3__ VCOS_BLOCKPOOL_SUBPOOL_T ;
struct TYPE_8__ {TYPE_3__* subpool; } ;
struct TYPE_11__ {TYPE_1__ owner; } ;
typedef  TYPE_4__ VCOS_BLOCKPOOL_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_POOL (TYPE_2__*) ; 
 int /*<<< orphan*/  ASSERT_SUBPOOL (TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

uint32_t vcos_generic_blockpool_is_valid_elem(
      VCOS_BLOCKPOOL_T *pool, const void *block)
{
   uint32_t ret = 0;
   const char *pool_end;
   VCOS_UNSIGNED i = 0;

   ASSERT_POOL(pool);
   if (((size_t) block) & 0x3)
      return 0;

   vcos_mutex_lock(&pool->mutex);

   for (i = 0; i < pool->num_subpools; ++i)
   {
      VCOS_BLOCKPOOL_SUBPOOL_T *subpool = &pool->subpools[i];
      ASSERT_SUBPOOL(subpool);

      if (subpool->mem && subpool->start)
      {
         pool_end = (const char*)subpool->start +
            (subpool->num_blocks * pool->block_size);

         if ((const char*)block > (const char*)subpool->start &&
               (const char*)block < pool_end)
         {
            const VCOS_BLOCKPOOL_HEADER_T *hdr = (
                  const VCOS_BLOCKPOOL_HEADER_T*) block - 1;

            /* If the block has a header where the owner points to the pool then
             * it's a valid block. */
            ret = (hdr->owner.subpool == subpool && subpool->owner == pool);
            break;
         }
      }
   }
   vcos_mutex_unlock(&pool->mutex);
   return ret;
}