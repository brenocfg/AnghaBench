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
struct zone {int dummy; } ;
struct page {int dummy; } ;
struct lruvec {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 struct lruvec* mem_cgroup_lru_add_list (struct zone*,struct page*,int) ; 
 int /*<<< orphan*/  mem_cgroup_lru_del_list (struct page*,int) ; 

struct lruvec *mem_cgroup_lru_move_lists(struct zone *zone,
					 struct page *page,
					 enum lru_list from,
					 enum lru_list to)
{
	/* XXX: Optimize this, especially for @from == @to */
	mem_cgroup_lru_del_list(page, from);
	return mem_cgroup_lru_add_list(zone, page, to);
}