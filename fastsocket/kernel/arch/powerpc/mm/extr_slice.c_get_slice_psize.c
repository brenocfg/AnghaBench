#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {int low_slices_psize; int high_slices_psize; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int GET_HIGH_SLICE_INDEX (unsigned long) ; 
 int GET_LOW_SLICE_INDEX (unsigned long) ; 
 unsigned long SLICE_LOW_TOP ; 

unsigned int get_slice_psize(struct mm_struct *mm, unsigned long addr)
{
	u64 psizes;
	int index;

	if (addr < SLICE_LOW_TOP) {
		psizes = mm->context.low_slices_psize;
		index = GET_LOW_SLICE_INDEX(addr);
	} else {
		psizes = mm->context.high_slices_psize;
		index = GET_HIGH_SLICE_INDEX(addr);
	}

	return (psizes >> (index * 4)) & 0xf;
}