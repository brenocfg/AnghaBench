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
struct bna_ioceth {TYPE_1__* bna; } ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; int /*<<< orphan*/  stats_mod; int /*<<< orphan*/  enet; } ;

/* Variables and functions */
 int /*<<< orphan*/  bna_enet_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_stats_mod_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnad_cb_ioceth_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_ioceth_sm_ready_entry(struct bna_ioceth *ioceth)
{
	bna_enet_start(&ioceth->bna->enet);
	bna_stats_mod_start(&ioceth->bna->stats_mod);
	bnad_cb_ioceth_ready(ioceth->bna->bnad);
}