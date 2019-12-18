#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_18__ {TYPE_2__* first; } ;
typedef  TYPE_1__ heap_cntrl ;
struct TYPE_19__ {scalar_t__ front_flag; scalar_t__ back_flag; struct TYPE_19__* prev; struct TYPE_19__* next; } ;
typedef  TYPE_2__ heap_block ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (void*) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (void*) ; 
 TYPE_2__* __lwp_heap_blockat (TYPE_2__*,void*) ; 
 scalar_t__ __lwp_heap_blockfree (TYPE_2__*) ; 
 int /*<<< orphan*/  __lwp_heap_blockin (TYPE_1__*,TYPE_2__*) ; 
 void* __lwp_heap_blocksize (TYPE_2__*) ; 
 TYPE_2__* __lwp_heap_head (TYPE_1__*) ; 
 TYPE_2__* __lwp_heap_nextblock (TYPE_2__*) ; 
 scalar_t__ __lwp_heap_prev_blockfree (TYPE_2__*) ; 
 TYPE_2__* __lwp_heap_prevblock (TYPE_2__*) ; 
 TYPE_2__* __lwp_heap_usrblockat (void*) ; 

BOOL __lwp_heap_free(heap_cntrl *theheap,void *ptr)
{
	heap_block *block;
	heap_block *next_block;
	heap_block *new_next;
	heap_block *prev_block;
	heap_block *tmp_block;
	u32 dsize,level;

	_CPU_ISR_Disable(level);

	block = __lwp_heap_usrblockat(ptr);
	if(!__lwp_heap_blockin(theheap,block) || __lwp_heap_blockfree(block)) {
		_CPU_ISR_Restore(level);
		return FALSE;
	}

	dsize = __lwp_heap_blocksize(block);
	next_block = __lwp_heap_blockat(block,dsize);

	if(!__lwp_heap_blockin(theheap,next_block) || (block->front_flag!=next_block->back_flag)) {
		_CPU_ISR_Restore(level);
		return FALSE;
	}

	if(__lwp_heap_prev_blockfree(block)) {
		prev_block = __lwp_heap_prevblock(block);
		if(!__lwp_heap_blockin(theheap,prev_block)) {
			_CPU_ISR_Restore(level);
			return FALSE;
		}

		if(__lwp_heap_blockfree(next_block)) {
			prev_block->front_flag += next_block->front_flag+dsize;
			tmp_block = __lwp_heap_nextblock(prev_block);
			tmp_block->back_flag = prev_block->front_flag;
			next_block->next->prev = next_block->prev;
			next_block->prev->next = next_block->next;
		} else {
			prev_block->front_flag = next_block->back_flag = prev_block->front_flag+dsize;
		}
	} else if(__lwp_heap_blockfree(next_block)) {
		block->front_flag = dsize+next_block->front_flag;
		new_next = __lwp_heap_nextblock(block);
		new_next->back_flag = block->front_flag;
		block->next = next_block->next;
		block->prev = next_block->prev;
		next_block->prev->next = block;
		next_block->next->prev = block;

		if(theheap->first==next_block) theheap->first = block;
	} else {
		next_block->back_flag = block->front_flag = dsize;
		block->prev = __lwp_heap_head(theheap);
		block->next = theheap->first;
		theheap->first = block;
		block->next->prev = block;
	}
	_CPU_ISR_Restore(level);

	return TRUE;
}