#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_1__* dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_dai; } ;

/* Variables and functions */
 int SND_SOC_DAIFMT_CBM_CFM ; 
 int SND_SOC_DAIFMT_DSP_A ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 int snd_soc_dai_set_fmt (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ams_delta_hw_params(struct snd_pcm_substream *substream,
			 struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;

	/* Set cpu DAI configuration */
	return snd_soc_dai_set_fmt(rtd->dai->cpu_dai,
				   SND_SOC_DAIFMT_DSP_A |
				   SND_SOC_DAIFMT_NB_NF |
				   SND_SOC_DAIFMT_CBM_CFM);
}