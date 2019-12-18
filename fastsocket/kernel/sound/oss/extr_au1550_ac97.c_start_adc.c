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
struct dmabuf {scalar_t__ nextIn; scalar_t__ dma_fragsize; scalar_t__ rawbuf; scalar_t__ dmasize; scalar_t__ stopped; int /*<<< orphan*/  dmanr; int /*<<< orphan*/  num_channels; } ;
struct au1550_state {struct dmabuf dma_adc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_AC97PCR ; 
 int /*<<< orphan*/  PSC_AC97PCR_RC ; 
 int /*<<< orphan*/  PSC_AC97PCR_RS ; 
 int /*<<< orphan*/  au1xxx_dbdma_put_dest (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  au1xxx_dbdma_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_recv_slots (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_adc(struct au1550_state *s)
{
	struct dmabuf  *db = &s->dma_adc;
	int	i;

	if (!db->stopped)
		return;

	/* Put two buffers on the ring to get things started.
	*/
	for (i=0; i<2; i++) {
		au1xxx_dbdma_put_dest(db->dmanr, db->nextIn, db->dma_fragsize);

		db->nextIn += db->dma_fragsize;
		if (db->nextIn >= db->rawbuf + db->dmasize)
			db->nextIn -= db->dmasize;
	}

	set_recv_slots(db->num_channels);
	au1xxx_dbdma_start(db->dmanr);
	au_writel(PSC_AC97PCR_RC, PSC_AC97PCR);
	au_sync();
	au_writel(PSC_AC97PCR_RS, PSC_AC97PCR);
	au_sync();

	db->stopped = 0;
}