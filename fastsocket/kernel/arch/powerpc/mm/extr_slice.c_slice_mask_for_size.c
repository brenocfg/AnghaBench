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
typedef  unsigned long u64 ;
struct slice_mask {unsigned int low_slices; unsigned int high_slices; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {unsigned long low_slices_psize; unsigned long high_slices_psize; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned long SLICE_NUM_HIGH ; 
 unsigned long SLICE_NUM_LOW ; 

__attribute__((used)) static struct slice_mask slice_mask_for_size(struct mm_struct *mm, int psize)
{
	struct slice_mask ret = { 0, 0 };
	unsigned long i;
	u64 psizes;

	psizes = mm->context.low_slices_psize;
	for (i = 0; i < SLICE_NUM_LOW; i++)
		if (((psizes >> (i * 4)) & 0xf) == psize)
			ret.low_slices |= 1u << i;

	psizes = mm->context.high_slices_psize;
	for (i = 0; i < SLICE_NUM_HIGH; i++)
		if (((psizes >> (i * 4)) & 0xf) == psize)
			ret.high_slices |= 1u << i;

	return ret;
}