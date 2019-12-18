#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int pg_size; TYPE_3__* first; } ;
typedef  TYPE_2__ heap_cntrl ;
struct TYPE_14__ {int front_flag; int back_flag; struct TYPE_14__* next; TYPE_1__* prev; } ;
typedef  TYPE_3__ heap_block ;
struct TYPE_12__ {TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEAP_BLOCK_USED ; 
 int HEAP_BLOCK_USED_OVERHEAD ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 TYPE_3__* __lwp_heap_blockat (TYPE_3__*,int) ; 
 void* __lwp_heap_buildflag (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* __lwp_heap_nextblock (TYPE_3__*) ; 
 void* __lwp_heap_startuser (TYPE_3__*) ; 
 TYPE_3__* __lwp_heap_tail (TYPE_2__*) ; 

void* __lwp_heap_allocate(heap_cntrl *theheap,u32 size)
{
	u32 excess;
	u32 dsize;
	heap_block *block;
	heap_block *next_block;
	heap_block *tmp_block;
	void *ptr;
	u32 offset,level;

	if(size>=(-1-HEAP_BLOCK_USED_OVERHEAD)) return NULL;

	_CPU_ISR_Disable(level);
	excess = (size % theheap->pg_size);
	dsize = (size + theheap->pg_size + HEAP_BLOCK_USED_OVERHEAD);

	if(excess)
		dsize += (theheap->pg_size - excess);

	if(dsize<sizeof(heap_block)) dsize = sizeof(heap_block);

	for(block=theheap->first;;block=block->next) {
		if(block==__lwp_heap_tail(theheap)) {
			_CPU_ISR_Restore(level);
			return NULL;
		}
		if(block->front_flag>=dsize) break;
	}

	if((block->front_flag-dsize)>(theheap->pg_size+HEAP_BLOCK_USED_OVERHEAD)) {
		block->front_flag -= dsize;
		next_block = __lwp_heap_nextblock(block);
		next_block->back_flag = block->front_flag;

		tmp_block = __lwp_heap_blockat(next_block,dsize);
		tmp_block->back_flag = next_block->front_flag = __lwp_heap_buildflag(dsize,HEAP_BLOCK_USED);

		ptr = __lwp_heap_startuser(next_block);
	} else {
		next_block = __lwp_heap_nextblock(block);
		next_block->back_flag = __lwp_heap_buildflag(block->front_flag,HEAP_BLOCK_USED);

		block->front_flag = next_block->back_flag;
		block->next->prev = block->prev;
		block->prev->next = block->next;

		ptr = __lwp_heap_startuser(block);
	}

	offset = (theheap->pg_size - ((u32)ptr&(theheap->pg_size-1)));
	ptr += offset;
	*(((u32*)ptr)-1) = offset;
	_CPU_ISR_Restore(level);

	return ptr;
}