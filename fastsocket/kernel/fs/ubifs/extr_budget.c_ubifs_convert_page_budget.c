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
struct ubifs_info {int budg_idx_growth; int max_idx_node_sz; int /*<<< orphan*/  space_lock; int /*<<< orphan*/  min_idx_lebs; scalar_t__ page_budget; int /*<<< orphan*/  budg_dd_growth; int /*<<< orphan*/  budg_data_growth; } ;

/* Variables and functions */
 int UBIFS_BLOCKS_PER_PAGE_SHIFT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_calc_min_idx_lebs (struct ubifs_info*) ; 

void ubifs_convert_page_budget(struct ubifs_info *c)
{
	spin_lock(&c->space_lock);
	/* Release the index growth reservation */
	c->budg_idx_growth -= c->max_idx_node_sz << UBIFS_BLOCKS_PER_PAGE_SHIFT;
	/* Release the data growth reservation */
	c->budg_data_growth -= c->page_budget;
	/* Increase the dirty data growth reservation instead */
	c->budg_dd_growth += c->page_budget;
	/* And re-calculate the indexing space reservation */
	c->min_idx_lebs = ubifs_calc_min_idx_lebs(c);
	spin_unlock(&c->space_lock);
}