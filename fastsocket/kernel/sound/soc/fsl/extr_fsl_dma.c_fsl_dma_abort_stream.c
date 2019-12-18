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

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STATE_XRUN ; 
 scalar_t__ snd_pcm_running (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stop (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irqsave (struct snd_pcm_substream*,unsigned long) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irqrestore (struct snd_pcm_substream*,unsigned long) ; 

__attribute__((used)) static void fsl_dma_abort_stream(struct snd_pcm_substream *substream)
{
	unsigned long flags;

	snd_pcm_stream_lock_irqsave(substream, flags);

	if (snd_pcm_running(substream))
		snd_pcm_stop(substream, SNDRV_PCM_STATE_XRUN);

	snd_pcm_stream_unlock_irqrestore(substream, flags);
}