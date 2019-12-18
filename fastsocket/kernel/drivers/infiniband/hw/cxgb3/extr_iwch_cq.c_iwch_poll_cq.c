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
struct iwch_dev {int dummy; } ;
struct iwch_cq {int /*<<< orphan*/  lock; struct iwch_dev* rhp; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int iwch_poll_cq_one (struct iwch_dev*,struct iwch_cq*,struct ib_wc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct iwch_cq* to_iwch_cq (struct ib_cq*) ; 

int iwch_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct iwch_dev *rhp;
	struct iwch_cq *chp;
	unsigned long flags;
	int npolled;
	int err = 0;

	chp = to_iwch_cq(ibcq);
	rhp = chp->rhp;

	spin_lock_irqsave(&chp->lock, flags);
	for (npolled = 0; npolled < num_entries; ++npolled) {
#ifdef DEBUG
		int i=0;
#endif

		/*
		 * Because T3 can post CQEs that are _not_ associated
		 * with a WR, we might have to poll again after removing
		 * one of these.
		 */
		do {
			err = iwch_poll_cq_one(rhp, chp, wc + npolled);
#ifdef DEBUG
			BUG_ON(++i > 1000);
#endif
		} while (err == -EAGAIN);
		if (err <= 0)
			break;
	}
	spin_unlock_irqrestore(&chp->lock, flags);

	if (err < 0)
		return err;
	else {
		return npolled;
	}
}