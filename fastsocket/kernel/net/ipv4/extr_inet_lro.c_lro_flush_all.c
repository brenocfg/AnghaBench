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
struct net_lro_mgr {int max_desc; struct net_lro_desc* lro_arr; } ;
struct net_lro_desc {scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  lro_flush (struct net_lro_mgr*,struct net_lro_desc*) ; 

void lro_flush_all(struct net_lro_mgr *lro_mgr)
{
	int i;
	struct net_lro_desc *lro_desc = lro_mgr->lro_arr;

	for (i = 0; i < lro_mgr->max_desc; i++) {
		if (lro_desc[i].active)
			lro_flush(lro_mgr, &lro_desc[i]);
	}
}