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
struct TYPE_2__ {int count; int fragsize; int sample_rate; int dma_bytes_per_sample; scalar_t__ stopped; int /*<<< orphan*/  ready; scalar_t__ mapped; } ;
struct au1550_state {TYPE_1__ dma_dac; scalar_t__ no_vra; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  au1550_delay (int) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
drain_dac(struct au1550_state *s, int nonblock)
{
	unsigned long   flags;
	int             count, tmo;

	if (s->dma_dac.mapped || !s->dma_dac.ready || s->dma_dac.stopped)
		return 0;

	for (;;) {
		spin_lock_irqsave(&s->lock, flags);
		count = s->dma_dac.count;
		spin_unlock_irqrestore(&s->lock, flags);
		if (count <= s->dma_dac.fragsize)
			break;
		if (signal_pending(current))
			break;
		if (nonblock)
			return -EBUSY;
		tmo = 1000 * count / (s->no_vra ?
				      48000 : s->dma_dac.sample_rate);
		tmo /= s->dma_dac.dma_bytes_per_sample;
		au1550_delay(tmo);
	}
	if (signal_pending(current))
		return -ERESTARTSYS;
	return 0;
}