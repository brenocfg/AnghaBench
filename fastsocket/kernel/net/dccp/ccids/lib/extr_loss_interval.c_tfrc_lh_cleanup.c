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
struct tfrc_loss_hist {scalar_t__ counter; int /*<<< orphan*/ ** ring; } ;

/* Variables and functions */
 size_t LIH_INDEX (scalar_t__) ; 
 scalar_t__ LIH_SIZE ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfrc_lh_is_initialised (struct tfrc_loss_hist*) ; 
 int /*<<< orphan*/  tfrc_lh_slab ; 

void tfrc_lh_cleanup(struct tfrc_loss_hist *lh)
{
	if (!tfrc_lh_is_initialised(lh))
		return;

	for (lh->counter = 0; lh->counter < LIH_SIZE; lh->counter++)
		if (lh->ring[LIH_INDEX(lh->counter)] != NULL) {
			kmem_cache_free(tfrc_lh_slab,
					lh->ring[LIH_INDEX(lh->counter)]);
			lh->ring[LIH_INDEX(lh->counter)] = NULL;
		}
}