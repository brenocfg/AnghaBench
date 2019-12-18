#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int /*<<< orphan*/ * ops; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ periods; scalar_t__ dma_bytes; scalar_t__ dma_addr; int /*<<< orphan*/ * dma_area; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * area; scalar_t__ bytes; scalar_t__ addr; } ;
struct TYPE_4__ {TYPE_1__ hw_buf; } ;
struct snd_cs46xx {TYPE_2__ capt; } ;

/* Variables and functions */
 scalar_t__ CS46XX_FRAGS ; 
 int /*<<< orphan*/  cs46xx_dsp_pcm_ostream_set_period (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_cs46xx_capture_indirect_ops ; 
 int /*<<< orphan*/  snd_cs46xx_capture_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs46xx_capture_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *hw_params)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	cs46xx_dsp_pcm_ostream_set_period (chip, params_period_bytes(hw_params));
#endif
	if (runtime->periods == CS46XX_FRAGS) {
		if (runtime->dma_area != chip->capt.hw_buf.area)
			snd_pcm_lib_free_pages(substream);
		runtime->dma_area = chip->capt.hw_buf.area;
		runtime->dma_addr = chip->capt.hw_buf.addr;
		runtime->dma_bytes = chip->capt.hw_buf.bytes;
		substream->ops = &snd_cs46xx_capture_ops;
	} else {
		if (runtime->dma_area == chip->capt.hw_buf.area) {
			runtime->dma_area = NULL;
			runtime->dma_addr = 0;
			runtime->dma_bytes = 0;
		}
		if ((err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params))) < 0)
			return err;
		substream->ops = &snd_cs46xx_capture_indirect_ops;
	}

	return 0;
}