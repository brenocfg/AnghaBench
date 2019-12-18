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
typedef  int u8 ;
typedef  int u32 ;
struct memb_blks {scalar_t__ num; int /*<<< orphan*/  size; scalar_t__ mem; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int MEM_ALIGN_SIZE (int /*<<< orphan*/ ) ; 

u8 memb_free(struct memb_blks *blk,void *ptr)
{
	s32 i;
	u32 *ptr2,*ptr1;

	ptr1 = ptr;
	ptr2 = (u32*)blk->mem;
	for(i=0;i<blk->num;i++) {
		if(ptr2==(ptr1 - 1)) {
			return --(*ptr2);
		}
		ptr2 = (u32*)(u8*)ptr2+(MEM_ALIGN_SIZE(blk->size)+sizeof(u32));
	}
	return -1;
}