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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int VCOS_UNSIGNED ;
struct TYPE_8__ {int block_size; scalar_t__ block_data_size; } ;
typedef  TYPE_2__ VCOS_BLOCKPOOL_T ;
struct TYPE_9__ {char* mem; char* start; int num_blocks; int available_blocks; TYPE_4__* free_list; TYPE_4__* end; TYPE_2__* owner; int /*<<< orphan*/  magic; } ;
typedef  TYPE_3__ VCOS_BLOCKPOOL_SUBPOOL_T ;
struct TYPE_7__ {TYPE_4__* next; } ;
struct TYPE_10__ {TYPE_1__ owner; } ;
typedef  TYPE_4__ VCOS_BLOCKPOOL_HEADER_T ;

/* Variables and functions */
 size_t VCOS_BLOCKPOOL_DEBUG_MEMSET_MAX_SIZE ; 
 scalar_t__ VCOS_BLOCKPOOL_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  VCOS_BLOCKPOOL_SUBPOOL_MAGIC ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  memset (char*,int,size_t) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,void*,...) ; 
 int /*<<< orphan*/  vcos_unused (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vcos_generic_blockpool_subpool_init(
      VCOS_BLOCKPOOL_T *pool, VCOS_BLOCKPOOL_SUBPOOL_T *subpool,
      void *mem, size_t pool_size, VCOS_UNSIGNED num_blocks, int align,
      uint32_t flags)
{
   VCOS_BLOCKPOOL_HEADER_T *block;
   VCOS_BLOCKPOOL_HEADER_T *end;

   vcos_unused(flags);

   vcos_log_trace(
         "%s: pool %p subpool %p mem %p pool_size %d " \
         "num_blocks %d align %d flags %x",
         VCOS_FUNCTION,
         pool, subpool, mem, (uint32_t) pool_size,
         num_blocks, align, flags);

   subpool->magic = VCOS_BLOCKPOOL_SUBPOOL_MAGIC;
   subpool->mem = mem;

   /* The block data pointers must be aligned according to align and the
    * block header pre-preceeds the first block data.
    * For large alignments there may be wasted space between subpool->mem
    * and the first block header.
    */
   subpool->start = (char *) subpool->mem + sizeof(VCOS_BLOCKPOOL_HEADER_T);
   subpool->start = (void*)
      VCOS_BLOCKPOOL_ROUND_UP((unsigned long) subpool->start, align);
   subpool->start = (char *) subpool->start - sizeof(VCOS_BLOCKPOOL_HEADER_T);

   vcos_assert(subpool->start >= subpool->mem);

   vcos_log_trace("%s: mem %p subpool->start %p" \
         " pool->block_size %d pool->block_data_size %d",
         VCOS_FUNCTION, mem, subpool->start,
         (int) pool->block_size, (int) pool->block_data_size);

   subpool->num_blocks = num_blocks;
   subpool->available_blocks = num_blocks;
   subpool->free_list = NULL;
   subpool->owner = pool;

   /* Initialise to a predictable bit pattern unless the pool is so big
    * that the delay would be noticeable. */
   if (pool_size < VCOS_BLOCKPOOL_DEBUG_MEMSET_MAX_SIZE)
      memset(subpool->mem, 0xBC, pool_size); /* For debugging */

   block = (VCOS_BLOCKPOOL_HEADER_T*) subpool->start;
   end = (VCOS_BLOCKPOOL_HEADER_T*)
      ((char *) subpool->start + (pool->block_size * num_blocks));
   subpool->end = end;

   /* Initialise the free list for this subpool */
   while (block < end)
   {
      block->owner.next = subpool->free_list;
      subpool->free_list = block;
      block = (VCOS_BLOCKPOOL_HEADER_T*)((char*) block + pool->block_size);
   }

}