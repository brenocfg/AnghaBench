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
struct kmmio_fault_page {int count; unsigned long page; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ arm_kmmio_fault_page (struct kmmio_fault_page*) ; 
 struct kmmio_fault_page* get_kmmio_fault_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct kmmio_fault_page*) ; 
 int /*<<< orphan*/  kmmio_page_list (unsigned long) ; 
 struct kmmio_fault_page* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_kmmio_fault_page(unsigned long page)
{
	struct kmmio_fault_page *f;

	page &= PAGE_MASK;
	f = get_kmmio_fault_page(page);
	if (f) {
		if (!f->count)
			arm_kmmio_fault_page(f);
		f->count++;
		return 0;
	}

	f = kzalloc(sizeof(*f), GFP_ATOMIC);
	if (!f)
		return -1;

	f->count = 1;
	f->page = page;

	if (arm_kmmio_fault_page(f)) {
		kfree(f);
		return -1;
	}

	list_add_rcu(&f->list, kmmio_page_list(f->page));

	return 0;
}