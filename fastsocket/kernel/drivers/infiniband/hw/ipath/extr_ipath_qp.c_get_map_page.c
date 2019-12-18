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
struct qpn_map {void* page; } ;
struct ipath_qp_table {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void get_map_page(struct ipath_qp_table *qpt, struct qpn_map *map)
{
	unsigned long page = get_zeroed_page(GFP_KERNEL);
	unsigned long flags;

	/*
	 * Free the page if someone raced with us installing it.
	 */

	spin_lock_irqsave(&qpt->lock, flags);
	if (map->page)
		free_page(page);
	else
		map->page = (void *)page;
	spin_unlock_irqrestore(&qpt->lock, flags);
}