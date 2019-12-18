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
struct TYPE_2__ {unsigned int id; scalar_t__ active; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned int MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_lock ; 
 int /*<<< orphan*/  context_map ; 
 int /*<<< orphan*/ ** context_mm ; 
 int /*<<< orphan*/  nr_free_contexts ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void destroy_context(struct mm_struct *mm)
{
	unsigned long flags;
	unsigned int id;

	if (mm->context.id == MMU_NO_CONTEXT)
		return;

	WARN_ON(mm->context.active != 0);

	spin_lock_irqsave(&context_lock, flags);
	id = mm->context.id;
	if (id != MMU_NO_CONTEXT) {
		__clear_bit(id, context_map);
		mm->context.id = MMU_NO_CONTEXT;
#ifdef DEBUG_MAP_CONSISTENCY
		mm->context.active = 0;
#endif
		context_mm[id] = NULL;
		nr_free_contexts++;
	}
	spin_unlock_irqrestore(&context_lock, flags);
}