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
struct dmabuf {scalar_t__ stopped; int /*<<< orphan*/  dmanr; int /*<<< orphan*/  num_channels; } ;
struct au1550_state {struct dmabuf dma_dac; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_AC97PCR ; 
 int /*<<< orphan*/  PSC_AC97PCR_TC ; 
 int /*<<< orphan*/  PSC_AC97PCR_TS ; 
 int /*<<< orphan*/  au1xxx_dbdma_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_xmit_slots (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_dac(struct au1550_state *s)
{
	struct dmabuf  *db = &s->dma_dac;

	if (!db->stopped)
		return;

	set_xmit_slots(db->num_channels);
	au_writel(PSC_AC97PCR_TC, PSC_AC97PCR);
	au_sync();
	au_writel(PSC_AC97PCR_TS, PSC_AC97PCR);
	au_sync();

	au1xxx_dbdma_start(db->dmanr);

	db->stopped = 0;
}