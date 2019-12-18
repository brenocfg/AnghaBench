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
struct ll_disk {int bitmap_index_changed; int (* commit ) (struct ll_disk*) ;} ;

/* Variables and functions */
 int stub1 (struct ll_disk*) ; 

int sm_ll_commit(struct ll_disk *ll)
{
	int r = 0;

	if (ll->bitmap_index_changed) {
		r = ll->commit(ll);
		if (!r)
			ll->bitmap_index_changed = false;
	}

	return r;
}