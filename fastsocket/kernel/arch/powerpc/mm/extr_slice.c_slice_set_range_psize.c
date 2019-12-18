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
struct slice_mask {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  slice_convert (struct mm_struct*,struct slice_mask,unsigned int) ; 
 struct slice_mask slice_range_to_mask (unsigned long,unsigned long) ; 

void slice_set_range_psize(struct mm_struct *mm, unsigned long start,
			   unsigned long len, unsigned int psize)
{
	struct slice_mask mask = slice_range_to_mask(start, len);

	slice_convert(mm, mask, psize);
}