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
struct azx_dev {unsigned int period_bytes; unsigned int bufsize; scalar_t__ insufficient; int /*<<< orphan*/ * posbuf; TYPE_1__* substream; } ;
struct azx {scalar_t__ remap_addr; } ;
struct TYPE_2__ {scalar_t__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_LPIB ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ VIA_IN_STREAM0_FIFO_SIZE_OFFSET ; 
 unsigned int azx_sd_readl (struct azx_dev*,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int readw (scalar_t__) ; 

__attribute__((used)) static unsigned int azx_via_get_position(struct azx *chip,
					 struct azx_dev *azx_dev)
{
	unsigned int link_pos, mini_pos, bound_pos;
	unsigned int mod_link_pos, mod_dma_pos, mod_mini_pos;
	unsigned int fifo_size;

	link_pos = azx_sd_readl(azx_dev, SD_LPIB);
	if (azx_dev->substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		/* Playback, no problem using link position */
		return link_pos;
	}

	/* Capture */
	/* For new chipset,
	 * use mod to get the DMA position just like old chipset
	 */
	mod_dma_pos = le32_to_cpu(*azx_dev->posbuf);
	mod_dma_pos %= azx_dev->period_bytes;

	/* azx_dev->fifo_size can't get FIFO size of in stream.
	 * Get from base address + offset.
	 */
	fifo_size = readw(chip->remap_addr + VIA_IN_STREAM0_FIFO_SIZE_OFFSET);

	if (azx_dev->insufficient) {
		/* Link position never gather than FIFO size */
		if (link_pos <= fifo_size)
			return 0;

		azx_dev->insufficient = 0;
	}

	if (link_pos <= fifo_size)
		mini_pos = azx_dev->bufsize + link_pos - fifo_size;
	else
		mini_pos = link_pos - fifo_size;

	/* Find nearest previous boudary */
	mod_mini_pos = mini_pos % azx_dev->period_bytes;
	mod_link_pos = link_pos % azx_dev->period_bytes;
	if (mod_link_pos >= fifo_size)
		bound_pos = link_pos - mod_link_pos;
	else if (mod_dma_pos >= mod_mini_pos)
		bound_pos = mini_pos - mod_mini_pos;
	else {
		bound_pos = mini_pos - mod_mini_pos + azx_dev->period_bytes;
		if (bound_pos >= azx_dev->bufsize)
			bound_pos = 0;
	}

	/* Calculate real DMA position we want */
	return bound_pos + mod_dma_pos;
}