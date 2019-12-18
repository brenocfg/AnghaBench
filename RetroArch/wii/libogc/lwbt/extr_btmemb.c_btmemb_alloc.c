#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct memb_blks {scalar_t__ num; int /*<<< orphan*/  size; scalar_t__ mem; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int MEM_ALIGN_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 

void* btmemb_alloc(struct memb_blks *blk)
{
	s32 i;
	u32 *ptr;
	u32 level;
	void *p;

	_CPU_ISR_Disable(level);
	ptr = (u32*)blk->mem;
	for(i=0;i<blk->num;i++) {
		if(*ptr==0) {
			++(*ptr);
			p = (ptr+1);
			_CPU_ISR_Restore(level);
			return p;
		}
		ptr = (u32*)((u8*)ptr+(MEM_ALIGN_SIZE(blk->size)+sizeof(u32)));
	}
	_CPU_ISR_Restore(level);
	return NULL;
}