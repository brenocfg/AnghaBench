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
struct page {int /*<<< orphan*/  _count; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_count (struct page*,int) ; 

__attribute__((used)) static inline void set_page_refcounted(struct page *page)
{
	VM_BUG_ON(PageTail(page));
	VM_BUG_ON(atomic_read(&page->_count));
	set_page_count(page, 1);
}