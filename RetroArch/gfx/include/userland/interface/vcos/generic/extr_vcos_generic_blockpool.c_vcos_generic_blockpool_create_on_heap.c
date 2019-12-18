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
typedef  int /*<<< orphan*/  VCOS_UNSIGNED ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_6__ {TYPE_1__* subpools; } ;
typedef  TYPE_2__ VCOS_BLOCKPOOL_T ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t VCOS_BLOCKPOOL_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCOS_BLOCKPOOL_SUBPOOL_FLAG_OWNS_MEM ; 
 scalar_t__ VCOS_ENOMEM ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  vcos_free (void*) ; 
 scalar_t__ vcos_generic_blockpool_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 void* vcos_malloc (size_t,char const*) ; 

VCOS_STATUS_T vcos_generic_blockpool_create_on_heap(VCOS_BLOCKPOOL_T *pool,
      VCOS_UNSIGNED num_blocks, VCOS_UNSIGNED block_size, VCOS_UNSIGNED align,
      VCOS_UNSIGNED flags, const char *name)
{
   VCOS_STATUS_T status = VCOS_SUCCESS;
   size_t size = VCOS_BLOCKPOOL_SIZE(num_blocks, block_size, align);
   void* mem = vcos_malloc(size, name);

   vcos_log_trace("%s: num_blocks %d block_size %d name %s",
         VCOS_FUNCTION, num_blocks, block_size, name);

   if (! mem)
      return VCOS_ENOMEM;

   status = vcos_generic_blockpool_init(pool, num_blocks,
         block_size, mem, size, align, flags, name);

   if (status != VCOS_SUCCESS)
      goto fail;

   pool->subpools[0].flags |= VCOS_BLOCKPOOL_SUBPOOL_FLAG_OWNS_MEM;
   return status;

fail:
   vcos_free(mem);
   return status;
}