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

/* Variables and functions */
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 unsigned int nfs_page_length (struct page*) ; 

__attribute__((used)) static void nfs_mark_uptodate(struct page *page, unsigned int base, unsigned int count)
{
	if (PageUptodate(page))
		return;
	if (base != 0)
		return;
	if (count != nfs_page_length(page))
		return;
	SetPageUptodate(page);
}