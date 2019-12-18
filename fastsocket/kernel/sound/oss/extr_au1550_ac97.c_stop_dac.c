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
struct dmabuf {int stopped; int /*<<< orphan*/  dmanr; } ;
struct au1550_state {int /*<<< orphan*/  lock; struct dmabuf dma_dac; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_AC97PCR ; 
 int /*<<< orphan*/  PSC_AC97PCR_TP ; 
 int /*<<< orphan*/  PSC_AC97STAT ; 
 int PSC_AC97STAT_TB ; 
 int /*<<< orphan*/  au1xxx_dbdma_reset (int /*<<< orphan*/ ) ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
stop_dac(struct au1550_state *s)
{
	struct dmabuf  *db = &s->dma_dac;
	u32		stat;
	unsigned long   flags;

	if (db->stopped)
		return;

	spin_lock_irqsave(&s->lock, flags);

	au_writel(PSC_AC97PCR_TP, PSC_AC97PCR);
	au_sync();

	/* Wait for Transmit Busy to show disabled.
	*/
	do {
		stat = au_readl(PSC_AC97STAT);
		au_sync();
	} while ((stat & PSC_AC97STAT_TB) != 0);

	au1xxx_dbdma_reset(db->dmanr);

	db->stopped = 1;

	spin_unlock_irqrestore(&s->lock, flags);
}