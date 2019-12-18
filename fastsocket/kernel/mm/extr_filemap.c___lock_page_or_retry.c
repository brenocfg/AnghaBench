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
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned int FAULT_FLAG_ALLOW_RETRY ; 
 unsigned int FAULT_FLAG_KILLABLE ; 
 int /*<<< orphan*/  __lock_page (struct page*) ; 
 int __lock_page_killable (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_locked_killable (struct page*) ; 

int __lock_page_or_retry(struct page *page, struct mm_struct *mm,
			 unsigned int flags)
{
	if (flags & FAULT_FLAG_ALLOW_RETRY) {
		up_read(&mm->mmap_sem);
		if (flags & FAULT_FLAG_KILLABLE)
			wait_on_page_locked_killable(page);
		else
			wait_on_page_locked(page);
		return 0;
	} else {
		if (flags & FAULT_FLAG_KILLABLE) {
			int ret;

			ret = __lock_page_killable(page);
			if (ret) {
				up_read(&mm->mmap_sem);
				return 0;
			}
		} else
			__lock_page(page);
		return 1;
	}
}