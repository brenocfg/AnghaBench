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
struct pagevec {int dummy; } ;
struct page {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int /*<<< orphan*/  ____pagevec_lru_add (struct pagevec*,int) ; 
 struct pagevec* get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_add_pvecs ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 

void __lru_cache_add(struct page *page, enum lru_list lru)
{
	struct pagevec *pvec = &get_cpu_var(lru_add_pvecs)[lru];

	page_cache_get(page);
	if (!pagevec_add(pvec, page))
		____pagevec_lru_add(pvec, lru);
	put_cpu_var(lru_add_pvecs);
}