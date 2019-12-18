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
struct TYPE_3__ {int size; int /*<<< orphan*/  ldt; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_4__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int LDT_ENTRY_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  clear_LDT () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  paravirt_free_ldt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

void destroy_context(struct mm_struct *mm)
{
	if (mm->context.size) {
#ifdef CONFIG_X86_32
		/* CHECKME: Can this ever happen ? */
		if (mm == current->active_mm)
			clear_LDT();
#endif
		paravirt_free_ldt(mm->context.ldt, mm->context.size);
		if (mm->context.size * LDT_ENTRY_SIZE > PAGE_SIZE)
			vfree(mm->context.ldt);
		else
			put_page(virt_to_page(mm->context.ldt));
		mm->context.size = 0;
	}
}