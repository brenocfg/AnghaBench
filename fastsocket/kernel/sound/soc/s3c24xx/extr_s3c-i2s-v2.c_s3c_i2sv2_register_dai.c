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
struct snd_soc_dai_ops {int /*<<< orphan*/  set_clkdiv; int /*<<< orphan*/  set_fmt; int /*<<< orphan*/  hw_params; int /*<<< orphan*/  trigger; } ;
struct snd_soc_dai {int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; struct snd_soc_dai_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  s3c2412_i2s_hw_params ; 
 int /*<<< orphan*/  s3c2412_i2s_resume ; 
 int /*<<< orphan*/  s3c2412_i2s_set_clkdiv ; 
 int /*<<< orphan*/  s3c2412_i2s_set_fmt ; 
 int /*<<< orphan*/  s3c2412_i2s_suspend ; 
 int /*<<< orphan*/  s3c2412_i2s_trigger ; 
 int snd_soc_register_dai (struct snd_soc_dai*) ; 

int s3c_i2sv2_register_dai(struct snd_soc_dai *dai)
{
	struct snd_soc_dai_ops *ops = dai->ops;

	ops->trigger = s3c2412_i2s_trigger;
	ops->hw_params = s3c2412_i2s_hw_params;
	ops->set_fmt = s3c2412_i2s_set_fmt;
	ops->set_clkdiv = s3c2412_i2s_set_clkdiv;

	dai->suspend = s3c2412_i2s_suspend;
	dai->resume = s3c2412_i2s_resume;

	return snd_soc_register_dai(dai);
}