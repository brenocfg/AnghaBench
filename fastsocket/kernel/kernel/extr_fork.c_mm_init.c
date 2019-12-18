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
struct task_struct {int dummy; } ;
struct mm_struct {int flags; unsigned long cached_hole_size; scalar_t__ def_flags; int /*<<< orphan*/  oom_disable_count; int /*<<< orphan*/  free_area_cache; int /*<<< orphan*/  page_table_lock; scalar_t__ nr_ptes; int /*<<< orphan*/ * core_state; int /*<<< orphan*/  mmlist; int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  mm_count; int /*<<< orphan*/  mm_users; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MMF_INIT_MASK ; 
 int /*<<< orphan*/  TASK_UNMAPPED_BASE ; 
 int /*<<< orphan*/  anon_rss ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* current ; 
 int default_dump_filter ; 
 int /*<<< orphan*/  file_rss ; 
 int /*<<< orphan*/  free_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mm_alloc_pgd (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_init_aio (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_init_owner (struct mm_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_mm_init (struct mm_struct*) ; 
 int /*<<< orphan*/  set_mm_counter (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_usage ; 

__attribute__((used)) static struct mm_struct * mm_init(struct mm_struct * mm, struct task_struct *p)
{
	atomic_set(&mm->mm_users, 1);
	atomic_set(&mm->mm_count, 1);
	init_rwsem(&mm->mmap_sem);
	INIT_LIST_HEAD(&mm->mmlist);
	mm->flags = (current->mm) ?
		(current->mm->flags & MMF_INIT_MASK) : default_dump_filter;
	mm->core_state = NULL;
	mm->nr_ptes = 0;
	set_mm_counter(mm, file_rss, 0);
	set_mm_counter(mm, anon_rss, 0);
	set_mm_counter(mm, swap_usage, 0);
	spin_lock_init(&mm->page_table_lock);
	mm->free_area_cache = TASK_UNMAPPED_BASE;
	mm->cached_hole_size = ~0UL;
	mm_init_aio(mm);
	mm_init_owner(mm, p);
	atomic_set(&mm->oom_disable_count, 0);

	if (likely(!mm_alloc_pgd(mm))) {
		mm->def_flags = 0;
		mmu_notifier_mm_init(mm);
		return mm;
	}

	free_mm(mm);
	return NULL;
}