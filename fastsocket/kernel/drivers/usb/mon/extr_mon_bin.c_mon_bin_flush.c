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
struct mon_reader_bin {int /*<<< orphan*/  fetch_lock; scalar_t__ b_read; int /*<<< orphan*/  b_lock; int /*<<< orphan*/  b_out; } ;
struct mon_bin_hdr {scalar_t__ len_cap; } ;

/* Variables and functions */
 struct mon_bin_hdr* MON_OFF2HDR (struct mon_reader_bin*,int /*<<< orphan*/ ) ; 
 scalar_t__ MON_RING_EMPTY (struct mon_reader_bin*) ; 
 scalar_t__ PKT_SIZE ; 
 int /*<<< orphan*/  mon_buff_area_free (struct mon_reader_bin*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mon_bin_flush(struct mon_reader_bin *rp, unsigned nevents)
{
	unsigned long flags;
	struct mon_bin_hdr *ep;
	int i;

	mutex_lock(&rp->fetch_lock);
	spin_lock_irqsave(&rp->b_lock, flags);
	for (i = 0; i < nevents; ++i) {
		if (MON_RING_EMPTY(rp))
			break;

		ep = MON_OFF2HDR(rp, rp->b_out);
		mon_buff_area_free(rp, PKT_SIZE + ep->len_cap);
	}
	spin_unlock_irqrestore(&rp->b_lock, flags);
	rp->b_read = 0;
	mutex_unlock(&rp->fetch_lock);
	return i;
}