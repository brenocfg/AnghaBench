#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct TYPE_6__ {TYPE_2__** top; } ;
struct TYPE_5__ {TYPE_1__** dir; } ;
struct TYPE_4__ {unsigned long* ent; } ;

/* Variables and functions */
 unsigned long EHEA_DIR_INDEX_SHIFT ; 
 unsigned long EHEA_INDEX_MASK ; 
 unsigned long EHEA_INVAL_ADDR ; 
 int EHEA_SECTSIZE ; 
 unsigned long EHEA_TOP_INDEX_SHIFT ; 
 unsigned long SECTION_SIZE_BITS ; 
 TYPE_3__* ehea_bmap ; 
 unsigned long virt_to_abs (void*) ; 

u64 ehea_map_vaddr(void *caddr)
{
	int top, dir, idx;
	unsigned long index, offset;

	if (!ehea_bmap)
		return EHEA_INVAL_ADDR;

	index = virt_to_abs(caddr) >> SECTION_SIZE_BITS;
	top = (index >> EHEA_TOP_INDEX_SHIFT) & EHEA_INDEX_MASK;
	if (!ehea_bmap->top[top])
		return EHEA_INVAL_ADDR;

	dir = (index >> EHEA_DIR_INDEX_SHIFT) & EHEA_INDEX_MASK;
	if (!ehea_bmap->top[top]->dir[dir])
		return EHEA_INVAL_ADDR;

	idx = index & EHEA_INDEX_MASK;
	if (!ehea_bmap->top[top]->dir[dir]->ent[idx])
		return EHEA_INVAL_ADDR;

	offset = (unsigned long)caddr & (EHEA_SECTSIZE - 1);
	return ehea_bmap->top[top]->dir[dir]->ent[idx] | offset;
}