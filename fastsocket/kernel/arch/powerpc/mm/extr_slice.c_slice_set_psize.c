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
 unsigned long GET_HIGH_SLICE_INDEX (unsigned long) ; 
 unsigned long GET_LOW_SLICE_INDEX (unsigned long) ; 
 unsigned long SLICE_LOW_TOP ; 
 int /*<<< orphan*/  slice_convert_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spu_flush_all_slbs (struct mm_struct*) ; 

void slice_set_psize(struct mm_struct *mm, unsigned long address,
		     unsigned int psize)
{
	unsigned long i, flags;
	u64 *p;

	spin_lock_irqsave(&slice_convert_lock, flags);
	if (address < SLICE_LOW_TOP) {
		i = GET_LOW_SLICE_INDEX(address);
		p = &mm->context.low_slices_psize;
	} else {
		i = GET_HIGH_SLICE_INDEX(address);
		p = &mm->context.high_slices_psize;
	}
	*p = (*p & ~(0xful << (i * 4))) | ((unsigned long) psize << (i * 4));
	spin_unlock_irqrestore(&slice_convert_lock, flags);

#ifdef CONFIG_SPU_BASE
	spu_flush_all_slbs(mm);
#endif
}