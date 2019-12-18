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
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 struct page* compound_head (struct page*) ; 
 scalar_t__ page_count (struct page*) ; 

__attribute__((used)) static inline void get_head_page_multiple(struct page *page, int nr)
{
	VM_BUG_ON(page != compound_head(page));
	VM_BUG_ON(page_count(page) == 0);
	atomic_add(nr, &page->_count);
}