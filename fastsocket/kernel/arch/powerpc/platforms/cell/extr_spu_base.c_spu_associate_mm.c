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
struct spu {struct mm_struct* mm; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mm_needs_global_tlbie (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spu_full_list_lock ; 

void spu_associate_mm(struct spu *spu, struct mm_struct *mm)
{
	unsigned long flags;

	spin_lock_irqsave(&spu_full_list_lock, flags);
	spu->mm = mm;
	spin_unlock_irqrestore(&spu_full_list_lock, flags);
	if (mm)
		mm_needs_global_tlbie(mm);
}