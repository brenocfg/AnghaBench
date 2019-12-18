#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ stats_get_busy; int /*<<< orphan*/  ioc_ready; } ;
struct bna {int /*<<< orphan*/  stats; int /*<<< orphan*/  bnad; TYPE_1__ stats_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_CB_BUSY ; 
 int /*<<< orphan*/  BNA_CB_FAIL ; 
 int /*<<< orphan*/  bna_bfi_stats_get (struct bna*) ; 
 int /*<<< orphan*/  bnad_cb_stats_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
bna_hw_stats_get(struct bna *bna)
{
	if (!bna->stats_mod.ioc_ready) {
		bnad_cb_stats_get(bna->bnad, BNA_CB_FAIL, &bna->stats);
		return;
	}
	if (bna->stats_mod.stats_get_busy) {
		bnad_cb_stats_get(bna->bnad, BNA_CB_BUSY, &bna->stats);
		return;
	}

	bna_bfi_stats_get(bna);
}