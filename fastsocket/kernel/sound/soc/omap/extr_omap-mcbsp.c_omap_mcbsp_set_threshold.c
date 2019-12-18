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
struct snd_soc_pcm_runtime {TYPE_1__* dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  private_data; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct omap_mcbsp_data {int /*<<< orphan*/  bus_id; } ;
struct TYPE_2__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 int MCBSP_DMA_MODE_THRESHOLD ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int omap_mcbsp_get_dma_op_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_mcbsp_set_rx_threshold (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_mcbsp_set_tx_threshold (int /*<<< orphan*/ ,int) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct omap_mcbsp_data* to_mcbsp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_mcbsp_set_threshold(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	struct omap_mcbsp_data *mcbsp_data = to_mcbsp(cpu_dai->private_data);
	int dma_op_mode = omap_mcbsp_get_dma_op_mode(mcbsp_data->bus_id);
	int samples;

	/* TODO: Currently, MODE_ELEMENT == MODE_FRAME */
	if (dma_op_mode == MCBSP_DMA_MODE_THRESHOLD)
		samples = snd_pcm_lib_period_bytes(substream) >> 1;
	else
		samples = 1;

	/* Configure McBSP internal buffer usage */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		omap_mcbsp_set_tx_threshold(mcbsp_data->bus_id, samples - 1);
	else
		omap_mcbsp_set_rx_threshold(mcbsp_data->bus_id, samples - 1);
}