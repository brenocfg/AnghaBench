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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_chan; } ;
struct atmel_ac97c {TYPE_1__ dma; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX_READY ; 
 int /*<<< orphan*/  dw_dma_cyclic_free (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct atmel_ac97c* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_ac97c_capture_hw_free(struct snd_pcm_substream *substream)
{
	struct atmel_ac97c *chip = snd_pcm_substream_chip(substream);
	if (test_and_clear_bit(DMA_RX_READY, &chip->flags))
		dw_dma_cyclic_free(chip->dma.rx_chan);
	return snd_pcm_lib_free_pages(substream);
}