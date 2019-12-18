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
struct nm256_stream {int shift; scalar_t__ buf; scalar_t__ dma_size; } ;
struct nm256 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_AUDIO_MUTE_REG ; 
 int /*<<< orphan*/  NM_PBUFFER_CURRP ; 
 int /*<<< orphan*/  NM_PBUFFER_END ; 
 int /*<<< orphan*/  NM_PBUFFER_START ; 
 int NM_PLAYBACK_ENABLE_FLAG ; 
 int /*<<< orphan*/  NM_PLAYBACK_ENABLE_REG ; 
 int NM_PLAYBACK_FREERUN ; 
 int /*<<< orphan*/  snd_nm256_playback_mark (struct nm256*,struct nm256_stream*) ; 
 int /*<<< orphan*/  snd_nm256_writeb (struct nm256*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_nm256_writel (struct nm256*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_nm256_writew (struct nm256*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
snd_nm256_playback_start(struct nm256 *chip, struct nm256_stream *s,
			 struct snd_pcm_substream *substream)
{
	/* program buffer pointers */
	snd_nm256_writel(chip, NM_PBUFFER_START, s->buf);
	snd_nm256_writel(chip, NM_PBUFFER_END, s->buf + s->dma_size - (1 << s->shift));
	snd_nm256_writel(chip, NM_PBUFFER_CURRP, s->buf);
	snd_nm256_playback_mark(chip, s);

	/* Enable playback engine and interrupts. */
	snd_nm256_writeb(chip, NM_PLAYBACK_ENABLE_REG,
			 NM_PLAYBACK_ENABLE_FLAG | NM_PLAYBACK_FREERUN);
	/* Enable both channels. */
	snd_nm256_writew(chip, NM_AUDIO_MUTE_REG, 0x0);
}