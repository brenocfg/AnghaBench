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
struct snd_soc_dai {int /*<<< orphan*/  active; int /*<<< orphan*/  private_data; } ;
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct omap_mcbsp_data {int bus_id; } ;
struct TYPE_2__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 int MCBSP_DMA_MODE_THRESHOLD ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int UINT_MAX ; 
 scalar_t__ cpu_is_omap343x () ; 
 int omap_mcbsp_get_dma_op_mode (int) ; 
 int omap_mcbsp_get_max_rx_threshold (int) ; 
 int omap_mcbsp_get_max_tx_threshold (int) ; 
 int omap_mcbsp_request (int) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct omap_mcbsp_data* to_mcbsp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_mcbsp_dai_startup(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	struct omap_mcbsp_data *mcbsp_data = to_mcbsp(cpu_dai->private_data);
	int bus_id = mcbsp_data->bus_id;
	int err = 0;

	if (!cpu_dai->active)
		err = omap_mcbsp_request(bus_id);

	if (cpu_is_omap343x()) {
		int dma_op_mode = omap_mcbsp_get_dma_op_mode(bus_id);
		int max_period;

		/*
		 * McBSP2 in OMAP3 has 1024 * 32-bit internal audio buffer.
		 * Set constraint for minimum buffer size to the same than FIFO
		 * size in order to avoid underruns in playback startup because
		 * HW is keeping the DMA request active until FIFO is filled.
		 */
		if (bus_id == 1)
			snd_pcm_hw_constraint_minmax(substream->runtime,
					SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					4096, UINT_MAX);

		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			max_period = omap_mcbsp_get_max_tx_threshold(bus_id);
		else
			max_period = omap_mcbsp_get_max_rx_threshold(bus_id);

		max_period++;
		max_period <<= 1;

		if (dma_op_mode == MCBSP_DMA_MODE_THRESHOLD)
			snd_pcm_hw_constraint_minmax(substream->runtime,
						SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
						32, max_period);
	}

	return err;
}