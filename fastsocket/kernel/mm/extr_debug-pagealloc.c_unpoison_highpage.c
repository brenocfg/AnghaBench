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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_poison (struct page*) ; 

__attribute__((used)) static void unpoison_highpage(struct page *page)
{
	/*
	 * See comment in poison_highpage().
	 * Highmem pages should not be poisoned for now
	 */
	BUG_ON(page_poison(page));
}