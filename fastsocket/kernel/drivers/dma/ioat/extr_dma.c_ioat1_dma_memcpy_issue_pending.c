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
struct ioat_dma_chan {scalar_t__ pending; int /*<<< orphan*/  desc_lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ioat1_dma_memcpy_issue_pending (struct ioat_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ioat_dma_chan* to_ioat_chan (struct dma_chan*) ; 

__attribute__((used)) static void ioat1_dma_memcpy_issue_pending(struct dma_chan *chan)
{
	struct ioat_dma_chan *ioat = to_ioat_chan(chan);

	if (ioat->pending > 0) {
		spin_lock_bh(&ioat->desc_lock);
		__ioat1_dma_memcpy_issue_pending(ioat);
		spin_unlock_bh(&ioat->desc_lock);
	}
}