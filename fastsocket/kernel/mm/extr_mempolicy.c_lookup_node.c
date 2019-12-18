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

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  current ; 
 int get_user_pages (int /*<<< orphan*/ ,struct mm_struct*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int lookup_node(struct mm_struct *mm, unsigned long addr)
{
	struct page *p;
	int err;

	err = get_user_pages(current, mm, addr & PAGE_MASK, 1, 0, 0, &p, NULL);
	if (err >= 0) {
		err = page_to_nid(p);
		put_page(p);
	}
	return err;
}