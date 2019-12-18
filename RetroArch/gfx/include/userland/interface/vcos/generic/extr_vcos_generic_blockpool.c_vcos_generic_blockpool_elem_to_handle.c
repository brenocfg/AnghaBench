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
typedef  int uint32_t ;
struct TYPE_8__ {size_t block_size; int num_subpools; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * subpools; } ;
typedef  TYPE_2__ VCOS_BLOCKPOOL_T ;
struct TYPE_9__ {int num_blocks; scalar_t__ start; TYPE_2__* owner; } ;
typedef  TYPE_3__ VCOS_BLOCKPOOL_SUBPOOL_T ;
struct TYPE_7__ {TYPE_3__* subpool; } ;
struct TYPE_10__ {TYPE_1__ owner; } ;
typedef  TYPE_4__ VCOS_BLOCKPOOL_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_POOL (TYPE_2__*) ; 
 int /*<<< orphan*/  ASSERT_SUBPOOL (TYPE_3__*) ; 
 int VCOS_BLOCKPOOL_HANDLE_CREATE (int,int) ; 
 int VCOS_BLOCKPOOL_MAX_SUBPOOLS ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

uint32_t vcos_generic_blockpool_elem_to_handle(void *block)
{
   uint32_t ret = -1;
   uint32_t index = -1;
   VCOS_BLOCKPOOL_HEADER_T *hdr = NULL;
   VCOS_BLOCKPOOL_T *pool = NULL;
   VCOS_BLOCKPOOL_SUBPOOL_T *subpool = NULL;
   uint32_t subpool_id;

   vcos_assert(block);
   hdr = (VCOS_BLOCKPOOL_HEADER_T*) block - 1;
   subpool = hdr->owner.subpool;
   ASSERT_SUBPOOL(subpool);

   pool = subpool->owner;
   ASSERT_POOL(pool);
   vcos_mutex_lock(&pool->mutex);

   /* The handle is the index into the array of blocks combined
    * with the subpool id.
    */
   index = ((size_t) hdr - (size_t) subpool->start) / pool->block_size;
   vcos_assert(index < subpool->num_blocks);

   subpool_id = ((char*) subpool - (char*) &pool->subpools[0]) /
      sizeof(VCOS_BLOCKPOOL_SUBPOOL_T);

   vcos_assert(subpool_id < VCOS_BLOCKPOOL_MAX_SUBPOOLS);
   vcos_assert(subpool_id < pool->num_subpools);
   ret = VCOS_BLOCKPOOL_HANDLE_CREATE(index, subpool_id);

   vcos_log_trace("%s: index %d subpool_id %d handle 0x%08x",
         VCOS_FUNCTION, index, subpool_id, ret);

   vcos_mutex_unlock(&pool->mutex);
   return ret;
}