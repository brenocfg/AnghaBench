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
struct snd_pcm_substream {int dummy; } ;
struct au1xpsc_audio_dmadata {int /*<<< orphan*/  ddma_chan; } ;

/* Variables and functions */
 size_t PCM_RX ; 
 size_t SUBSTREAM_TYPE (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  au1x_pcm_queue_rx (struct au1xpsc_audio_dmadata*) ; 
 int /*<<< orphan*/  au1x_pcm_queue_tx (struct au1xpsc_audio_dmadata*) ; 
 struct au1xpsc_audio_dmadata** au1xpsc_audio_pcmdma ; 
 int /*<<< orphan*/  au1xxx_dbdma_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1xpsc_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct au1xpsc_audio_dmadata *pcd =
			au1xpsc_audio_pcmdma[SUBSTREAM_TYPE(substream)];

	au1xxx_dbdma_reset(pcd->ddma_chan);

	if (SUBSTREAM_TYPE(substream) == PCM_RX) {
		au1x_pcm_queue_rx(pcd);
		au1x_pcm_queue_rx(pcd);
	} else {
		au1x_pcm_queue_tx(pcd);
		au1x_pcm_queue_tx(pcd);
	}

	return 0;
}