#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  context; } ;
struct TYPE_4__ {struct mm_struct* active_mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 TYPE_1__* get_paca () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  slb_flush_and_rebolt () ; 

__attribute__((used)) static void slice_flush_segments(void *parm)
{
	struct mm_struct *mm = parm;
	unsigned long flags;

	if (mm != current->active_mm)
		return;

	/* update the paca copy of the context struct */
	get_paca()->context = current->active_mm->context;

	local_irq_save(flags);
	slb_flush_and_rebolt();
	local_irq_restore(flags);
}