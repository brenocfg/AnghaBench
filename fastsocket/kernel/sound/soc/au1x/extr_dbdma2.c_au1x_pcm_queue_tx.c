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
struct au1xpsc_audio_dmadata {scalar_t__ q_period; scalar_t__ periods; int /*<<< orphan*/  dma_area_s; int /*<<< orphan*/  dma_area; scalar_t__ period_bytes; int /*<<< orphan*/  ddma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDMA_FLAGS_IE ; 
 int /*<<< orphan*/  au1xxx_dbdma_put_source_flags (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1x_pcm_queue_tx(struct au1xpsc_audio_dmadata *cd)
{
	au1xxx_dbdma_put_source_flags(cd->ddma_chan,
				(void *)phys_to_virt(cd->dma_area),
				cd->period_bytes, DDMA_FLAGS_IE);

	/* update next-to-queue period */
	++cd->q_period;
	cd->dma_area += cd->period_bytes;
	if (cd->q_period >= cd->periods) {
		cd->q_period = 0;
		cd->dma_area = cd->dma_area_s;
	}
}