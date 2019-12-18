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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_FORMAT ; 
 int EINVAL ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int sffsdr_fpga_set_codec_fs (int) ; 
 int snd_soc_dai_set_fmt (struct snd_soc_dai*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sffsdr_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	int fs;
	int ret = 0;

	/* Fsref can be 32000, 44100 or 48000. */
	fs = params_rate(params);

#ifndef CONFIG_SFFSDR_FPGA
	/* Without the FPGA module, the Fs is fixed at 44100 Hz */
	if (fs != 44100) {
		pr_debug("warning: only 44.1 kHz is supported without SFFSDR FPGA module\n");
		return -EINVAL;
	}
#endif

	/* set cpu DAI configuration */
	ret = snd_soc_dai_set_fmt(cpu_dai, AUDIO_FORMAT);
	if (ret < 0)
		return ret;

	pr_debug("sffsdr_hw_params: rate = %d Hz\n", fs);

#ifndef CONFIG_SFFSDR_FPGA
	return 0;
#else
	return sffsdr_fpga_set_codec_fs(fs);
#endif
}