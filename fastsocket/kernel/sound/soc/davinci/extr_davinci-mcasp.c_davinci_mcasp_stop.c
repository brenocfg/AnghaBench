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
struct davinci_audio_dev {scalar_t__ base; scalar_t__ rxnumevt; scalar_t__ txnumevt; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_RFIFOCTL ; 
 scalar_t__ DAVINCI_MCASP_WFIFOCTL ; 
 int /*<<< orphan*/  FIFO_ENABLE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  mcasp_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_stop_rx (struct davinci_audio_dev*) ; 
 int /*<<< orphan*/  mcasp_stop_tx (struct davinci_audio_dev*) ; 

__attribute__((used)) static void davinci_mcasp_stop(struct davinci_audio_dev *dev, int stream)
{
	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		if (dev->txnumevt)	/* disable FIFO */
			mcasp_clr_bits(dev->base + DAVINCI_MCASP_WFIFOCTL,
								FIFO_ENABLE);
		mcasp_stop_tx(dev);
	} else {
		if (dev->rxnumevt)	/* disable FIFO */
			mcasp_clr_bits(dev->base + DAVINCI_MCASP_RFIFOCTL,
								FIFO_ENABLE);
		mcasp_stop_rx(dev);
	}
}