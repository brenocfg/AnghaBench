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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; void* ldt; } ;
typedef  TYPE_1__ mm_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LDT_ENTRY_SIZE ; 
 int PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  flush_ldt ; 
 int /*<<< orphan*/  load_LDT (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mm_cpumask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paravirt_alloc_ldt (void*,int) ; 
 int /*<<< orphan*/  paravirt_free_ldt (void*,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  vfree (void*) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 
 void* vmalloc (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int alloc_ldt(mm_context_t *pc, int mincount, int reload)
{
	void *oldldt, *newldt;
	int oldsize;

	if (mincount <= pc->size)
		return 0;
	oldsize = pc->size;
	mincount = (mincount + (PAGE_SIZE / LDT_ENTRY_SIZE - 1)) &
			(~(PAGE_SIZE / LDT_ENTRY_SIZE - 1));
	if (mincount * LDT_ENTRY_SIZE > PAGE_SIZE)
		newldt = vmalloc(mincount * LDT_ENTRY_SIZE);
	else
		newldt = (void *)__get_free_page(GFP_KERNEL);

	if (!newldt)
		return -ENOMEM;

	if (oldsize)
		memcpy(newldt, pc->ldt, oldsize * LDT_ENTRY_SIZE);
	oldldt = pc->ldt;
	memset(newldt + oldsize * LDT_ENTRY_SIZE, 0,
	       (mincount - oldsize) * LDT_ENTRY_SIZE);

	paravirt_alloc_ldt(newldt, mincount);

#ifdef CONFIG_X86_64
	/* CHECKME: Do we really need this ? */
	wmb();
#endif
	pc->ldt = newldt;
	wmb();
	pc->size = mincount;
	wmb();

	if (reload) {
#ifdef CONFIG_SMP
		preempt_disable();
		load_LDT(pc);
		if (!cpumask_equal(mm_cpumask(current->mm),
				   cpumask_of(smp_processor_id())))
			smp_call_function(flush_ldt, current->mm, 1);
		preempt_enable();
#else
		load_LDT(pc);
#endif
	}
	if (oldsize) {
		paravirt_free_ldt(oldldt, oldsize);
		if (oldsize * LDT_ENTRY_SIZE > PAGE_SIZE)
			vfree(oldldt);
		else
			put_page(virt_to_page(oldldt));
	}
	return 0;
}