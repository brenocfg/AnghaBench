#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_3__* ops; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int silence_size; int boundary; int silence_start; scalar_t__ silence_filled; scalar_t__ buffer_size; scalar_t__ silence_threshold; scalar_t__ access; char* dma_area; scalar_t__ channels; unsigned int dma_bytes; int /*<<< orphan*/  format; TYPE_2__* status; TYPE_1__* control; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
typedef  scalar_t__ snd_pcm_sframes_t ;
struct TYPE_6__ {int (* silence ) (struct snd_pcm_substream*,int,scalar_t__,scalar_t__) ;} ;
struct TYPE_5__ {int hw_ptr; } ;
struct TYPE_4__ {int appl_ptr; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_ACCESS_MMAP_INTERLEAVED ; 
 scalar_t__ SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 scalar_t__ ULONG_MAX ; 
 int frames_to_bytes (struct snd_pcm_runtime*,scalar_t__) ; 
 int samples_to_bytes (struct snd_pcm_runtime*,scalar_t__) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_pcm_format_set_silence (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ snd_pcm_playback_hw_avail (struct snd_pcm_runtime*) ; 
 int stub1 (struct snd_pcm_substream*,int,scalar_t__,scalar_t__) ; 
 int stub2 (struct snd_pcm_substream*,unsigned int,scalar_t__,scalar_t__) ; 

void snd_pcm_playback_silence(struct snd_pcm_substream *substream, snd_pcm_uframes_t new_hw_ptr)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_uframes_t frames, ofs, transfer;

	if (runtime->silence_size < runtime->boundary) {
		snd_pcm_sframes_t noise_dist, n;
		if (runtime->silence_start != runtime->control->appl_ptr) {
			n = runtime->control->appl_ptr - runtime->silence_start;
			if (n < 0)
				n += runtime->boundary;
			if ((snd_pcm_uframes_t)n < runtime->silence_filled)
				runtime->silence_filled -= n;
			else
				runtime->silence_filled = 0;
			runtime->silence_start = runtime->control->appl_ptr;
		}
		if (runtime->silence_filled >= runtime->buffer_size)
			return;
		noise_dist = snd_pcm_playback_hw_avail(runtime) + runtime->silence_filled;
		if (noise_dist >= (snd_pcm_sframes_t) runtime->silence_threshold)
			return;
		frames = runtime->silence_threshold - noise_dist;
		if (frames > runtime->silence_size)
			frames = runtime->silence_size;
	} else {
		if (new_hw_ptr == ULONG_MAX) {	/* initialization */
			snd_pcm_sframes_t avail = snd_pcm_playback_hw_avail(runtime);
			runtime->silence_filled = avail > 0 ? avail : 0;
			runtime->silence_start = (runtime->status->hw_ptr +
						  runtime->silence_filled) %
						 runtime->boundary;
		} else {
			ofs = runtime->status->hw_ptr;
			frames = new_hw_ptr - ofs;
			if ((snd_pcm_sframes_t)frames < 0)
				frames += runtime->boundary;
			runtime->silence_filled -= frames;
			if ((snd_pcm_sframes_t)runtime->silence_filled < 0) {
				runtime->silence_filled = 0;
				runtime->silence_start = new_hw_ptr;
			} else {
				runtime->silence_start = ofs;
			}
		}
		frames = runtime->buffer_size - runtime->silence_filled;
	}
	if (snd_BUG_ON(frames > runtime->buffer_size))
		return;
	if (frames == 0)
		return;
	ofs = runtime->silence_start % runtime->buffer_size;
	while (frames > 0) {
		transfer = ofs + frames > runtime->buffer_size ? runtime->buffer_size - ofs : frames;
		if (runtime->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED ||
		    runtime->access == SNDRV_PCM_ACCESS_MMAP_INTERLEAVED) {
			if (substream->ops->silence) {
				int err;
				err = substream->ops->silence(substream, -1, ofs, transfer);
				snd_BUG_ON(err < 0);
			} else {
				char *hwbuf = runtime->dma_area + frames_to_bytes(runtime, ofs);
				snd_pcm_format_set_silence(runtime->format, hwbuf, transfer * runtime->channels);
			}
		} else {
			unsigned int c;
			unsigned int channels = runtime->channels;
			if (substream->ops->silence) {
				for (c = 0; c < channels; ++c) {
					int err;
					err = substream->ops->silence(substream, c, ofs, transfer);
					snd_BUG_ON(err < 0);
				}
			} else {
				size_t dma_csize = runtime->dma_bytes / channels;
				for (c = 0; c < channels; ++c) {
					char *hwbuf = runtime->dma_area + (c * dma_csize) + samples_to_bytes(runtime, ofs);
					snd_pcm_format_set_silence(runtime->format, hwbuf, transfer);
				}
			}
		}
		runtime->silence_filled += transfer;
		frames -= transfer;
		ofs = 0;
	}
}