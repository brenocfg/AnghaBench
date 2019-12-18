#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t VCOS_UNSIGNED ;
struct TYPE_9__ {size_t num_subpools; int /*<<< orphan*/  mutex; int /*<<< orphan*/  align; int /*<<< orphan*/  block_data_size; TYPE_2__* subpools; } ;
typedef  TYPE_1__ VCOS_BLOCKPOOL_T ;
struct TYPE_10__ {int flags; int /*<<< orphan*/ * start; TYPE_1__* mem; int /*<<< orphan*/  num_blocks; } ;
typedef  TYPE_2__ VCOS_BLOCKPOOL_SUBPOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_POOL (TYPE_1__*) ; 
 int /*<<< orphan*/  ASSERT_SUBPOOL (TYPE_2__*) ; 
 int VCOS_BLOCKPOOL_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VCOS_BLOCKPOOL_SUBPOOL_FLAG_OWNS_MEM ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 

void vcos_generic_blockpool_delete(VCOS_BLOCKPOOL_T *pool)
{
   vcos_log_trace("%s: pool %p", VCOS_FUNCTION, pool);

   if (pool)
   {
      VCOS_UNSIGNED i;

      ASSERT_POOL(pool);
      for (i = 0; i < pool->num_subpools; ++i)
      {
         VCOS_BLOCKPOOL_SUBPOOL_T *subpool = &pool->subpools[i];
         ASSERT_SUBPOOL(subpool);
         if (subpool->mem)
         {
            /* For debugging */
            memset(subpool->mem,
                  0xBE,
                  VCOS_BLOCKPOOL_SIZE(subpool->num_blocks,
                     pool->block_data_size, pool->align));

            if (subpool->flags & VCOS_BLOCKPOOL_SUBPOOL_FLAG_OWNS_MEM)
               vcos_free(subpool->mem);
            subpool->mem = NULL;
            subpool->start = NULL;
         }
      }
      vcos_mutex_delete(&pool->mutex);
      memset(pool, 0xBE, sizeof(VCOS_BLOCKPOOL_T)); /* For debugging */
   }
}