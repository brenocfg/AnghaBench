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
typedef  int VCOS_UNSIGNED ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_7__ {int num_subpools; int num_extension_blocks; TYPE_1__* subpools; } ;
typedef  TYPE_2__ VCOS_BLOCKPOOL_T ;
struct TYPE_6__ {int /*<<< orphan*/ * mem; int /*<<< orphan*/ * start; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_POOL (TYPE_2__*) ; 
 int VCOS_BLOCKPOOL_MAX_SUBPOOLS ; 
 int /*<<< orphan*/  VCOS_BLOCKPOOL_SUBPOOL_MAGIC ; 
 int /*<<< orphan*/  VCOS_EACCESS ; 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,TYPE_2__*,int,int) ; 

VCOS_STATUS_T vcos_generic_blockpool_extend(VCOS_BLOCKPOOL_T *pool,
      VCOS_UNSIGNED num_extensions, VCOS_UNSIGNED num_blocks)
{
   VCOS_UNSIGNED i;
   ASSERT_POOL(pool);

   vcos_log_trace("%s: pool %p num_extensions %d num_blocks %d",
         VCOS_FUNCTION, pool, num_extensions, num_blocks);

   /* Extend may only be called once */
   if (pool->num_subpools > 1)
      return VCOS_EACCESS;

   if (num_extensions < 1 ||
         num_extensions > VCOS_BLOCKPOOL_MAX_SUBPOOLS - 1)
      return VCOS_EINVAL;

   if (num_blocks < 1)
      return VCOS_EINVAL;

   pool->num_subpools += num_extensions;
   pool->num_extension_blocks = num_blocks;

   /* Mark these subpools as valid but unallocated */
   for (i = 1; i < pool->num_subpools; ++i)
   {
      pool->subpools[i].magic = VCOS_BLOCKPOOL_SUBPOOL_MAGIC;
      pool->subpools[i].start = NULL;
      pool->subpools[i].mem = NULL;
   }

   return VCOS_SUCCESS;
}