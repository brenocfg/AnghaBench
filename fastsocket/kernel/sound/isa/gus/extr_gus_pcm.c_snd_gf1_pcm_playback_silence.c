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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_area; int /*<<< orphan*/  format; struct gus_pcm_private* private_data; } ;
struct snd_gus_card {int dummy; } ;
struct gus_pcm_private {int dma_size; scalar_t__ memory; struct snd_gus_card* gus; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int EIO ; 
 int samples_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_gf1_pcm_block_change (struct snd_pcm_substream*,unsigned int,scalar_t__,unsigned int) ; 
 int snd_gf1_pcm_poke_block (struct snd_gus_card*,scalar_t__,scalar_t__,unsigned int,int,int) ; 
 scalar_t__ snd_gf1_pcm_use_dma ; 
 int /*<<< orphan*/  snd_pcm_format_set_silence (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int snd_pcm_format_unsigned (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_gf1_pcm_playback_silence(struct snd_pcm_substream *substream,
					int voice,
					snd_pcm_uframes_t pos,
					snd_pcm_uframes_t count)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct gus_pcm_private *pcmp = runtime->private_data;
	unsigned int bpos, len;
	
	bpos = samples_to_bytes(runtime, pos) + (voice * (pcmp->dma_size / 2));
	len = samples_to_bytes(runtime, count);
	if (snd_BUG_ON(bpos > pcmp->dma_size))
		return -EIO;
	if (snd_BUG_ON(bpos + len > pcmp->dma_size))
		return -EIO;
	snd_pcm_format_set_silence(runtime->format, runtime->dma_area + bpos, count);
	if (snd_gf1_pcm_use_dma && len > 32) {
		return snd_gf1_pcm_block_change(substream, bpos, pcmp->memory + bpos, len);
	} else {
		struct snd_gus_card *gus = pcmp->gus;
		int err, w16, invert;

		w16 = (snd_pcm_format_width(runtime->format) == 16);
		invert = snd_pcm_format_unsigned(runtime->format);
		if ((err = snd_gf1_pcm_poke_block(gus, runtime->dma_area + bpos, pcmp->memory + bpos, len, w16, invert)) < 0)
			return err;
	}
	return 0;
}