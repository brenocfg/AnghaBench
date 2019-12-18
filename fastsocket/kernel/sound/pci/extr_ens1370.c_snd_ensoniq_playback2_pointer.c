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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct ensoniq {int /*<<< orphan*/  reg_lock; } ;
typedef  size_t snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  DAC2_SIZE ; 
 int ES_DAC2_EN ; 
 int /*<<< orphan*/  ES_MEM_PAGEO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_PAGE_DAC ; 
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 size_t ES_REG_FCURR_COUNTI (int) ; 
 int /*<<< orphan*/  MEM_PAGE ; 
 size_t bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ensoniq* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_ensoniq_playback2_pointer(struct snd_pcm_substream *substream)
{
	struct ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	size_t ptr;

	spin_lock(&ensoniq->reg_lock);
	if (inl(ES_REG(ensoniq, CONTROL)) & ES_DAC2_EN) {
		outl(ES_MEM_PAGEO(ES_PAGE_DAC), ES_REG(ensoniq, MEM_PAGE));
		ptr = ES_REG_FCURR_COUNTI(inl(ES_REG(ensoniq, DAC2_SIZE)));
		ptr = bytes_to_frames(substream->runtime, ptr);
	} else {
		ptr = 0;
	}
	spin_unlock(&ensoniq->reg_lock);
	return ptr;
}