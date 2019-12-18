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
struct ioat_chan_common {int /*<<< orphan*/  cleanup_lock; int /*<<< orphan*/  completion; } ;
struct ioat_dma_chan {int /*<<< orphan*/  desc_lock; struct ioat_chan_common base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cleanup (struct ioat_dma_chan*,unsigned long) ; 
 int /*<<< orphan*/  ioat_cleanup_preamble (struct ioat_chan_common*,unsigned long*) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_trylock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ioat1_cleanup(struct ioat_dma_chan *ioat)
{
	struct ioat_chan_common *chan = &ioat->base;
	unsigned long phys_complete;

	prefetch(chan->completion);

	if (!spin_trylock_bh(&chan->cleanup_lock))
		return;

	if (!ioat_cleanup_preamble(chan, &phys_complete)) {
		spin_unlock_bh(&chan->cleanup_lock);
		return;
	}

	if (!spin_trylock_bh(&ioat->desc_lock)) {
		spin_unlock_bh(&chan->cleanup_lock);
		return;
	}

	__cleanup(ioat, phys_complete);

	spin_unlock_bh(&ioat->desc_lock);
	spin_unlock_bh(&chan->cleanup_lock);
}