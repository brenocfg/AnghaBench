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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  periods; int /*<<< orphan*/  dma_addr; struct omap_runtime_data* private_data; } ;
struct omap_runtime_data {int /*<<< orphan*/  dma_ch; struct omap_pcm_dma_data* dma_data; } ;
struct omap_pcm_dma_data {int /*<<< orphan*/  port_addr; int /*<<< orphan*/  sync_mode; int /*<<< orphan*/  dma_req; } ;
struct omap_dma_channel_params {int elem_count; int /*<<< orphan*/  frame_count; void* src_port; int /*<<< orphan*/  dst_start; int /*<<< orphan*/  src_start; int /*<<< orphan*/  src_or_dst_synch; void* dst_amode; void* src_amode; void* dst_port; int /*<<< orphan*/  sync_mode; int /*<<< orphan*/  trigger; int /*<<< orphan*/  data_type; } ;
typedef  int /*<<< orphan*/  dma_params ;

/* Variables and functions */
 void* OMAP_DMA_AMODE_CONSTANT ; 
 void* OMAP_DMA_AMODE_POST_INC ; 
 int OMAP_DMA_BLOCK_IRQ ; 
 int /*<<< orphan*/  OMAP_DMA_DATA_BURST_16 ; 
 int /*<<< orphan*/  OMAP_DMA_DATA_TYPE_S16 ; 
 int /*<<< orphan*/  OMAP_DMA_DST_SYNC ; 
 int OMAP_DMA_FRAME_IRQ ; 
 int OMAP_DMA_LAST_IRQ ; 
 void* OMAP_DMA_PORT_MPUI ; 
 int /*<<< orphan*/  OMAP_DMA_SRC_SYNC ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  cpu_class_is_omap1 () ; 
 scalar_t__ cpu_is_omap1510 () ; 
 int /*<<< orphan*/  memset (struct omap_dma_channel_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_enable_dma_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_set_dma_dest_burst_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_params (int /*<<< orphan*/ ,struct omap_dma_channel_params*) ; 
 int /*<<< orphan*/  omap_set_dma_src_burst_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static int omap_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct omap_runtime_data *prtd = runtime->private_data;
	struct omap_pcm_dma_data *dma_data = prtd->dma_data;
	struct omap_dma_channel_params dma_params;

	/* return if this is a bufferless transfer e.g.
	 * codec <--> BT codec or GSM modem -- lg FIXME */
	if (!prtd->dma_data)
		return 0;

	memset(&dma_params, 0, sizeof(dma_params));
	/*
	 * Note: Regardless of interface data formats supported by OMAP McBSP
	 * or EAC blocks, internal representation is always fixed 16-bit/sample
	 */
	dma_params.data_type			= OMAP_DMA_DATA_TYPE_S16;
	dma_params.trigger			= dma_data->dma_req;
	dma_params.sync_mode			= dma_data->sync_mode;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		dma_params.src_amode		= OMAP_DMA_AMODE_POST_INC;
		dma_params.dst_amode		= OMAP_DMA_AMODE_CONSTANT;
		dma_params.src_or_dst_synch	= OMAP_DMA_DST_SYNC;
		dma_params.src_start		= runtime->dma_addr;
		dma_params.dst_start		= dma_data->port_addr;
		dma_params.dst_port		= OMAP_DMA_PORT_MPUI;
	} else {
		dma_params.src_amode		= OMAP_DMA_AMODE_CONSTANT;
		dma_params.dst_amode		= OMAP_DMA_AMODE_POST_INC;
		dma_params.src_or_dst_synch	= OMAP_DMA_SRC_SYNC;
		dma_params.src_start		= dma_data->port_addr;
		dma_params.dst_start		= runtime->dma_addr;
		dma_params.src_port		= OMAP_DMA_PORT_MPUI;
	}
	/*
	 * Set DMA transfer frame size equal to ALSA period size and frame
	 * count as no. of ALSA periods. Then with DMA frame interrupt enabled,
	 * we can transfer the whole ALSA buffer with single DMA transfer but
	 * still can get an interrupt at each period bounary
	 */
	dma_params.elem_count	= snd_pcm_lib_period_bytes(substream) / 2;
	dma_params.frame_count	= runtime->periods;
	omap_set_dma_params(prtd->dma_ch, &dma_params);

	if ((cpu_is_omap1510()) &&
			(substream->stream == SNDRV_PCM_STREAM_PLAYBACK))
		omap_enable_dma_irq(prtd->dma_ch, OMAP_DMA_FRAME_IRQ |
			      OMAP_DMA_LAST_IRQ | OMAP_DMA_BLOCK_IRQ);
	else
		omap_enable_dma_irq(prtd->dma_ch, OMAP_DMA_FRAME_IRQ);

	if (!(cpu_class_is_omap1())) {
		omap_set_dma_src_burst_mode(prtd->dma_ch,
						OMAP_DMA_DATA_BURST_16);
		omap_set_dma_dest_burst_mode(prtd->dma_ch,
						OMAP_DMA_DATA_BURST_16);
	}

	return 0;
}