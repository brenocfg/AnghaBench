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
struct snd_pcm_hw_rule {scalar_t__ private; } ;
struct snd_pcm_hw_params {unsigned int msbits; } ;
struct snd_interval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_interval_single (struct snd_interval*) ; 
 int snd_interval_value (struct snd_interval*) ; 

__attribute__((used)) static int snd_pcm_hw_rule_msbits(struct snd_pcm_hw_params *params,
				  struct snd_pcm_hw_rule *rule)
{
	unsigned int l = (unsigned long) rule->private;
	int width = l & 0xffff;
	unsigned int msbits = l >> 16;
	struct snd_interval *i = hw_param_interval(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS);
	if (snd_interval_single(i) && snd_interval_value(i) == width)
		params->msbits = msbits;
	return 0;
}