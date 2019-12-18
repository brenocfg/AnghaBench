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
struct ioat2_dma_chan {int /*<<< orphan*/  ring_lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ioat2_issue_pending (struct ioat2_dma_chan*) ; 
 scalar_t__ ioat2_ring_pending (struct ioat2_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ioat2_dma_chan* to_ioat2_chan (struct dma_chan*) ; 

void ioat2_issue_pending(struct dma_chan *c)
{
	struct ioat2_dma_chan *ioat = to_ioat2_chan(c);

	if (ioat2_ring_pending(ioat)) {
		spin_lock_bh(&ioat->ring_lock);
		__ioat2_issue_pending(ioat);
		spin_unlock_bh(&ioat->ring_lock);
	}
}