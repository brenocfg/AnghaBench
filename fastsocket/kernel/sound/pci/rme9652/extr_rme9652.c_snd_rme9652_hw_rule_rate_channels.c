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
struct snd_rme9652 {scalar_t__ ss_channels; scalar_t__ ds_channels; } ;
struct snd_pcm_hw_rule {struct snd_rme9652* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {scalar_t__ min; int max; int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 

__attribute__((used)) static int snd_rme9652_hw_rule_rate_channels(struct snd_pcm_hw_params *params,
					     struct snd_pcm_hw_rule *rule)
{
	struct snd_rme9652 *rme9652 = rule->private;
	struct snd_interval *c = hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval *r = hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	if (c->min >= rme9652->ss_channels) {
		struct snd_interval t = {
			.min = 44100,
			.max = 48000,
			.integer = 1,
		};
		return snd_interval_refine(r, &t);
	} else if (c->max <= rme9652->ds_channels) {
		struct snd_interval t = {
			.min = 88200,
			.max = 96000,
			.integer = 1,
		};
		return snd_interval_refine(r, &t);
	}
	return 0;
}