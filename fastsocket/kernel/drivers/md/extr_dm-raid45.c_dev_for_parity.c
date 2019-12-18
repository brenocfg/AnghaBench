#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int parity; } ;
struct stripe {TYPE_2__ idx; int /*<<< orphan*/  key; int /*<<< orphan*/  sc; } ;
struct TYPE_6__ {int dev_to_init; int pi; TYPE_1__* raid_type; } ;
struct raid_set {TYPE_3__ set; } ;
struct TYPE_4__ {scalar_t__ level; } ;

/* Variables and functions */
 int DM_RH_NOSYNC ; 
 int DM_RH_RECOVERING ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StripeRecover (struct stripe*) ; 
 scalar_t__ raid4 ; 
 int region_state (struct raid_set*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dev_for_parity(struct stripe *stripe, int *sync)
{
	struct raid_set *rs = RS(stripe->sc);
	int r = region_state(rs, stripe->key, DM_RH_NOSYNC | DM_RH_RECOVERING);

	*sync = !r;

	/* Reconstruct a particular device ?. */
	if (r && rs->set.dev_to_init > -1)
		return rs->set.dev_to_init;
	else if (rs->set.raid_type->level == raid4)
		return rs->set.pi;
	else if (!StripeRecover(stripe))
		return stripe->idx.parity;
	else
		return -1;
}