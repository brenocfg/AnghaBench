#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct snd_m3 {int dummy; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct m3_dma {TYPE_1__ inst; } ;
struct TYPE_5__ {scalar_t__ val; scalar_t__ addr; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ CDATA_DMA_CONTROL ; 
 scalar_t__ DMACONTROL_AUTOREPEAT ; 
 scalar_t__ DMACONTROL_DIRECTION ; 
 scalar_t__ DMAC_BLOCKF_SELECTOR ; 
 scalar_t__ DMAC_PAGE3_SELECTOR ; 
 int /*<<< orphan*/  MEMTYPE_INTERNAL_DATA ; 
 scalar_t__ SRC3_DIRECTION_OFFSET ; 
 TYPE_2__* rv ; 
 int /*<<< orphan*/  snd_m3_assp_write (struct snd_m3*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
snd_m3_capture_setup(struct snd_m3 *chip, struct m3_dma *s, struct snd_pcm_substream *subs)
{
	unsigned int i;

	/*
	 * some per client initializers
	 */

	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_DIRECTION_OFFSET + 12,
			  s->inst.data + 40 + 8);

	/* tell it which way dma is going? */
	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_DMA_CONTROL,
			  DMACONTROL_DIRECTION + DMACONTROL_AUTOREPEAT + 
			  DMAC_PAGE3_SELECTOR + DMAC_BLOCKF_SELECTOR);

	/*
	 * set an armload of static initializers
	 */
	for (i = 0; i < ARRAY_SIZE(rv); i++) 
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
				  s->inst.data + rv[i].addr, rv[i].val);
}