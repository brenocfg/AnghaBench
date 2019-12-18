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
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct ipath_user_pages_work {size_t num_pages; int /*<<< orphan*/  work; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ipath_release_user_pages (struct page**,size_t,int) ; 
 int /*<<< orphan*/  current ; 
 struct mm_struct* get_task_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_wq ; 
 struct ipath_user_pages_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_pages_account ; 

void ipath_release_user_pages_on_close(struct page **p, size_t num_pages)
{
	struct ipath_user_pages_work *work;
	struct mm_struct *mm;

	__ipath_release_user_pages(p, num_pages, 1);

	mm = get_task_mm(current);
	if (!mm)
		return;

	work = kmalloc(sizeof(*work), GFP_KERNEL);
	if (!work)
		goto bail_mm;

	INIT_WORK(&work->work, user_pages_account);
	work->mm = mm;
	work->num_pages = num_pages;

	queue_work(ib_wq, &work->work);
	return;

bail_mm:
	mmput(mm);
	return;
}