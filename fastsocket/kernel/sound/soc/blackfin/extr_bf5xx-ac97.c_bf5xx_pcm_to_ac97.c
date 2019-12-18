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
struct ac97_frame {int /*<<< orphan*/  ac97_tag; int /*<<< orphan*/  ac97_center; int /*<<< orphan*/  ac97_lfe; int /*<<< orphan*/  ac97_sr; int /*<<< orphan*/  ac97_sl; int /*<<< orphan*/  ac97_pcm_l; int /*<<< orphan*/  ac97_pcm_r; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 unsigned int SP_FC ; 
 unsigned int SP_FL ; 
 unsigned int SP_FR ; 
 unsigned int SP_LFE ; 
 unsigned int SP_SL ; 
 unsigned int SP_SR ; 
 int /*<<< orphan*/  TAG_PCM_CENTER ; 
 int /*<<< orphan*/  TAG_PCM_LEFT ; 
 int /*<<< orphan*/  TAG_PCM_LFE ; 
 int /*<<< orphan*/  TAG_PCM_RIGHT ; 
 int /*<<< orphan*/  TAG_PCM_SL ; 
 int /*<<< orphan*/  TAG_PCM_SR ; 
 int /*<<< orphan*/  TAG_VALID ; 

void bf5xx_pcm_to_ac97(struct ac97_frame *dst, const __u16 *src,
		size_t count, unsigned int chan_mask)
{
	while (count--) {
		dst->ac97_tag = TAG_VALID;
		if (chan_mask & SP_FL) {
			dst->ac97_pcm_r = *src++;
			dst->ac97_tag |= TAG_PCM_RIGHT;
		}
		if (chan_mask & SP_FR) {
			dst->ac97_pcm_l = *src++;
			dst->ac97_tag |= TAG_PCM_LEFT;

		}
#if defined(CONFIG_SND_BF5XX_MULTICHAN_SUPPORT)
		if (chan_mask & SP_SR) {
			dst->ac97_sl = *src++;
			dst->ac97_tag |= TAG_PCM_SL;
		}
		if (chan_mask & SP_SL) {
			dst->ac97_sr = *src++;
			dst->ac97_tag |= TAG_PCM_SR;
		}
		if (chan_mask & SP_LFE) {
			dst->ac97_lfe = *src++;
			dst->ac97_tag |= TAG_PCM_LFE;
		}
		if (chan_mask & SP_FC) {
			dst->ac97_center = *src++;
			dst->ac97_tag |= TAG_PCM_CENTER;
		}
#endif
		dst++;
	}
}