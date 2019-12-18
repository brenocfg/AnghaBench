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
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {unsigned int max; unsigned int min; int /*<<< orphan*/  openmin; scalar_t__ openmax; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_hw_params*) ; 
 struct snd_pcm_hw_params* kmalloc (int,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_param_near (struct snd_pcm_substream*,struct snd_pcm_hw_params*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int snd_pcm_hw_param_set (struct snd_pcm_substream*,struct snd_pcm_hw_params*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int choose_rate(struct snd_pcm_substream *substream,
		       struct snd_pcm_hw_params *params, unsigned int best_rate)
{
	struct snd_interval *it;
	struct snd_pcm_hw_params *save;
	unsigned int rate, prev;

	save = kmalloc(sizeof(*save), GFP_KERNEL);
	if (save == NULL)
		return -ENOMEM;
	*save = *params;
	it = hw_param_interval(save, SNDRV_PCM_HW_PARAM_RATE);

	/* try multiples of the best rate */
	rate = best_rate;
	for (;;) {
		if (it->max < rate || (it->max == rate && it->openmax))
			break;
		if (it->min < rate || (it->min == rate && !it->openmin)) {
			int ret;
			ret = snd_pcm_hw_param_set(substream, params,
						   SNDRV_PCM_HW_PARAM_RATE,
						   rate, 0);
			if (ret == (int)rate) {
				kfree(save);
				return rate;
			}
			*params = *save;
		}
		prev = rate;
		rate += best_rate;
		if (rate <= prev)
			break;
	}

	/* not found, use the nearest rate */
	kfree(save);
	return snd_pcm_hw_param_near(substream, params, SNDRV_PCM_HW_PARAM_RATE, best_rate, NULL);
}