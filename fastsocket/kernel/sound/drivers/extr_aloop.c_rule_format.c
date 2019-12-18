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
typedef  int /*<<< orphan*/  u_int32_t ;
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct snd_pcm_hardware* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_pcm_hardware {int formats; } ;
struct snd_mask {int /*<<< orphan*/ * bits; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_MASK_MAX ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rule_format(struct snd_pcm_hw_params *params,
		       struct snd_pcm_hw_rule *rule)
{

	struct snd_pcm_hardware *hw = rule->private;
	struct snd_mask *maskp = hw_param_mask(params, rule->var);

	maskp->bits[0] &= (u_int32_t)hw->formats;
	maskp->bits[1] &= (u_int32_t)(hw->formats >> 32);
	memset(maskp->bits + 2, 0, (SNDRV_MASK_MAX-64) / 8); /* clear rest */
	if (! maskp->bits[0] && ! maskp->bits[1])
		return -EINVAL;
	return 0;
}