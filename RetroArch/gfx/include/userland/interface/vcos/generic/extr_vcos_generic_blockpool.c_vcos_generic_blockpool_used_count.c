#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t VCOS_UNSIGNED ;
struct TYPE_6__ {size_t num_subpools; int /*<<< orphan*/  mutex; TYPE_2__* subpools; } ;
typedef  TYPE_1__ VCOS_BLOCKPOOL_T ;
struct TYPE_7__ {scalar_t__ available_blocks; scalar_t__ num_blocks; scalar_t__ start; } ;
typedef  TYPE_2__ VCOS_BLOCKPOOL_SUBPOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_POOL (TYPE_1__*) ; 
 int /*<<< orphan*/  ASSERT_SUBPOOL (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

VCOS_UNSIGNED vcos_generic_blockpool_used_count(VCOS_BLOCKPOOL_T *pool)
{
   VCOS_UNSIGNED ret = 0;
   VCOS_UNSIGNED i;

   ASSERT_POOL(pool);
   vcos_mutex_lock(&pool->mutex);

   for (i = 0; i < pool->num_subpools; ++i)
   {
      VCOS_BLOCKPOOL_SUBPOOL_T *subpool = &pool->subpools[i];
      ASSERT_SUBPOOL(subpool);
      if (subpool->start)
         ret += (subpool->num_blocks - subpool->available_blocks);
   }
   vcos_mutex_unlock(&pool->mutex);
   return ret;
}