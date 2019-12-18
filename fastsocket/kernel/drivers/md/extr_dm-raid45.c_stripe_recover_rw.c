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
struct stripe {TYPE_1__* recover; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SetStripeMerged (struct stripe*) ; 
 scalar_t__ TestClearStripeMerged (struct stripe*) ; 
 scalar_t__ TestClearStripeRBW (struct stripe*) ; 
 int /*<<< orphan*/  dev_for_parity (struct stripe*,int*) ; 
 int stripe_recover_read (struct stripe*,int /*<<< orphan*/ ) ; 
 int stripe_recover_write (struct stripe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stripe_recover_rw(struct stripe *stripe)
{
	int r = 0, sync = 0;

	/* Read/write flip-flop. */
	if (TestClearStripeRBW(stripe)) {
		SetStripeMerged(stripe);
		stripe->key = stripe->recover->pos;
		r = stripe_recover_read(stripe, dev_for_parity(stripe, &sync));
		BUG_ON(!r);
	} else if (TestClearStripeMerged(stripe)) {
		r = stripe_recover_write(stripe, dev_for_parity(stripe, &sync));
		BUG_ON(!r);
	}

	BUG_ON(sync);
	return r;
}