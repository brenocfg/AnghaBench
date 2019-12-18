#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_5__ {size_t locked_vm; } ;
struct TYPE_4__ {TYPE_2__* mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  __ipath_release_user_pages (struct page**,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int get_user_pages (TYPE_1__*,TYPE_2__*,unsigned long,size_t,int,int,struct page**,struct vm_area_struct**) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ipath_get_user_pages(unsigned long start_page, size_t num_pages,
				  struct page **p, struct vm_area_struct **vma)
{
	unsigned long lock_limit;
	size_t got;
	int ret;

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

	if (num_pages > lock_limit) {
		ret = -ENOMEM;
		goto bail;
	}

	ipath_cdbg(VERBOSE, "pin %lx pages from vaddr %lx\n",
		   (unsigned long) num_pages, start_page);

	for (got = 0; got < num_pages; got += ret) {
		ret = get_user_pages(current, current->mm,
				     start_page + got * PAGE_SIZE,
				     num_pages - got, 1, 1,
				     p + got, vma);
		if (ret < 0)
			goto bail_release;
	}

	current->mm->locked_vm += num_pages;

	ret = 0;
	goto bail;

bail_release:
	__ipath_release_user_pages(p, got, 0);
bail:
	return ret;
}