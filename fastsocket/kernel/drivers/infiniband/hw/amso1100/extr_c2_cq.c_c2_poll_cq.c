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
struct ib_wc {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct c2_dev {int dummy; } ;
struct c2_cq {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int c2_poll_one (struct c2_dev*,struct c2_cq*,struct ib_wc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct c2_cq* to_c2cq (struct ib_cq*) ; 
 struct c2_dev* to_c2dev (int /*<<< orphan*/ ) ; 

int c2_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *entry)
{
	struct c2_dev *c2dev = to_c2dev(ibcq->device);
	struct c2_cq *cq = to_c2cq(ibcq);
	unsigned long flags;
	int npolled, err;

	spin_lock_irqsave(&cq->lock, flags);

	for (npolled = 0; npolled < num_entries; ++npolled) {

		err = c2_poll_one(c2dev, cq, entry + npolled);
		if (err)
			break;
	}

	spin_unlock_irqrestore(&cq->lock, flags);

	return npolled;
}