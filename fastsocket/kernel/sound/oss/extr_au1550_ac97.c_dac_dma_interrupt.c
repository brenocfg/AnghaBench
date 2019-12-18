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
typedef  int u32 ;
struct dmabuf {scalar_t__ count; scalar_t__ fragsize; scalar_t__ nextOut; scalar_t__ rawbuf; scalar_t__ dmasize; int /*<<< orphan*/  wait; int /*<<< orphan*/  dma_qcount; scalar_t__ dma_fragsize; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  dmanr; } ;
struct au1550_state {int /*<<< orphan*/  lock; struct dmabuf dma_dac; } ;

/* Variables and functions */
 int AC97C_TE ; 
 int AC97C_XO ; 
 int AC97C_XU ; 
 int /*<<< orphan*/  PSC_AC97STAT ; 
 scalar_t__ au1xxx_dbdma_put_source (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dac_dma_interrupt(int irq, void *dev_id)
{
	struct au1550_state *s = (struct au1550_state *) dev_id;
	struct dmabuf  *db = &s->dma_dac;
	u32	ac97c_stat;

	spin_lock(&s->lock);

	ac97c_stat = au_readl(PSC_AC97STAT);
	if (ac97c_stat & (AC97C_XU | AC97C_XO | AC97C_TE))
		pr_debug("AC97C status = 0x%08x\n", ac97c_stat);
	db->dma_qcount--;

	if (db->count >= db->fragsize) {
		if (au1xxx_dbdma_put_source(db->dmanr, db->nextOut,
							db->fragsize) == 0) {
			err("qcount < 2 and no ring room!");
		}
		db->nextOut += db->fragsize;
		if (db->nextOut >= db->rawbuf + db->dmasize)
			db->nextOut -= db->dmasize;
		db->count -= db->fragsize;
		db->total_bytes += db->dma_fragsize;
		db->dma_qcount++;
	}

	/* wake up anybody listening */
	if (waitqueue_active(&db->wait))
		wake_up(&db->wait);

	spin_unlock(&s->lock);
}