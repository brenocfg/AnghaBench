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
typedef  scalar_t__ u32 ;
struct dmabuf {scalar_t__ count; scalar_t__ dmasize; scalar_t__ nextIn; scalar_t__ dma_fragsize; scalar_t__ rawbuf; int /*<<< orphan*/  wait; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  dmanr; int /*<<< orphan*/  error; } ;
struct au1550_state {int /*<<< orphan*/  lock; struct dmabuf dma_adc; } ;

/* Variables and functions */
 int /*<<< orphan*/  au1xxx_dbdma_get_dest (int /*<<< orphan*/ ,void*,scalar_t__*) ; 
 int /*<<< orphan*/  au1xxx_dbdma_put_dest (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_adc (struct au1550_state*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adc_dma_interrupt(int irq, void *dev_id)
{
	struct	au1550_state *s = (struct au1550_state *)dev_id;
	struct	dmabuf  *dp = &s->dma_adc;
	u32	obytes;
	char	*obuf;

	spin_lock(&s->lock);

	/* Pull the buffer from the dma queue.
	*/
	au1xxx_dbdma_get_dest(dp->dmanr, (void *)(&obuf), &obytes);

	if ((dp->count + obytes) > dp->dmasize) {
		/* Overrun. Stop ADC and log the error
		*/
		spin_unlock(&s->lock);
		stop_adc(s);
		dp->error++;
		err("adc overrun");
		return;
	}

	/* Put a new empty buffer on the destination DMA.
	*/
	au1xxx_dbdma_put_dest(dp->dmanr, dp->nextIn, dp->dma_fragsize);

	dp->nextIn += dp->dma_fragsize;
	if (dp->nextIn >= dp->rawbuf + dp->dmasize)
		dp->nextIn -= dp->dmasize;

	dp->count += obytes;
	dp->total_bytes += obytes;

	/* wake up anybody listening
	*/
	if (waitqueue_active(&dp->wait))
		wake_up(&dp->wait);

	spin_unlock(&s->lock);
}