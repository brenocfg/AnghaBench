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
typedef  void* u32 ;
struct snd_usb_substream {int /*<<< orphan*/  dev; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {void** bits; } ;
struct snd_interval {scalar_t__ min; scalar_t__ max; scalar_t__ openmax; scalar_t__ openmin; } ;
struct audioformat {int formats; scalar_t__ channels; scalar_t__ rate_min; scalar_t__ rate_max; int datainterval; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_TIME ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ USB_SPEED_FULL ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwc_debug (char*,unsigned int,...) ; 
 scalar_t__ snd_mask_empty (struct snd_mask*) ; 
 int /*<<< orphan*/  snd_mask_intersect (struct snd_mask*,struct snd_mask*) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 scalar_t__ snd_usb_get_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_check_valid_format(struct snd_usb_substream *subs,
				 struct snd_pcm_hw_params *params,
				 struct audioformat *fp)
{
	struct snd_interval *it = hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	struct snd_interval *ct = hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_mask *fmts = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	struct snd_interval *pt = hw_param_interval(params, SNDRV_PCM_HW_PARAM_PERIOD_TIME);
	struct snd_mask check_fmts;
	unsigned int ptime;

	/* check the format */
	snd_mask_none(&check_fmts);
	check_fmts.bits[0] = (u32)fp->formats;
	check_fmts.bits[1] = (u32)(fp->formats >> 32);
	snd_mask_intersect(&check_fmts, fmts);
	if (snd_mask_empty(&check_fmts)) {
		hwc_debug("   > check: no supported format %d\n", fp->format);
		return 0;
	}
	/* check the channels */
	if (fp->channels < ct->min || fp->channels > ct->max) {
		hwc_debug("   > check: no valid channels %d (%d/%d)\n", fp->channels, ct->min, ct->max);
		return 0;
	}
	/* check the rate is within the range */
	if (fp->rate_min > it->max || (fp->rate_min == it->max && it->openmax)) {
		hwc_debug("   > check: rate_min %d > max %d\n", fp->rate_min, it->max);
		return 0;
	}
	if (fp->rate_max < it->min || (fp->rate_max == it->min && it->openmin)) {
		hwc_debug("   > check: rate_max %d < min %d\n", fp->rate_max, it->min);
		return 0;
	}
	/* check whether the period time is >= the data packet interval */
	if (snd_usb_get_speed(subs->dev) != USB_SPEED_FULL) {
		ptime = 125 * (1 << fp->datainterval);
		if (ptime > pt->max || (ptime == pt->max && pt->openmax)) {
			hwc_debug("   > check: ptime %u > max %u\n", ptime, pt->max);
			return 0;
		}
	}
	return 1;
}