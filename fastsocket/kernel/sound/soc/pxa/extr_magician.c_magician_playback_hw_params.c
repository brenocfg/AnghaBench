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
struct TYPE_2__ {struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  PXA_SSP_AUDIO_DIV_ACDS ; 
 int /*<<< orphan*/  PXA_SSP_AUDIO_DIV_SCDB ; 
 int /*<<< orphan*/  PXA_SSP_CLK_AUDIO ; 
 unsigned int PXA_SSP_CLK_AUDIO_DIV_1 ; 
 unsigned int PXA_SSP_CLK_AUDIO_DIV_16 ; 
 unsigned int PXA_SSP_CLK_AUDIO_DIV_2 ; 
 unsigned int PXA_SSP_CLK_AUDIO_DIV_4 ; 
 unsigned int PXA_SSP_CLK_AUDIO_DIV_8 ; 
 unsigned int PXA_SSP_CLK_SCDB_1 ; 
 unsigned int PXA_SSP_CLK_SCDB_4 ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_OUT ; 
 int SND_SOC_DAIFMT_CBS_CFS ; 
 int SND_SOC_DAIFMT_DSP_A ; 
 int SND_SOC_DAIFMT_MSB ; 
 int SND_SOC_DAIFMT_NB_IF ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 unsigned int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_clkdiv (struct snd_soc_dai*,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_soc_dai_set_fmt (struct snd_soc_dai*,int) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_tdm_slot (struct snd_soc_dai*,int,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int magician_playback_hw_params(struct snd_pcm_substream *substream,
				       struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->dai->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	unsigned int acps, acds, width, rate;
	unsigned int div4 = PXA_SSP_CLK_SCDB_4;
	int ret = 0;

	rate = params_rate(params);
	width = snd_pcm_format_physical_width(params_format(params));

	/*
	 * rate = SSPSCLK / (2 * width(16 or 32))
	 * SSPSCLK = (ACPS / ACDS) / SSPSCLKDIV(div4 or div1)
	 */
	switch (params_rate(params)) {
	case 8000:
		/* off by a factor of 2: bug in the PXA27x audio clock? */
		acps = 32842000;
		switch (width) {
		case 16:
			/* 513156 Hz ~= _2_ * 8000 Hz * 32 (+0.23%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_16;
			break;
		default: /* 32 */
			/* 1026312 Hz ~= _2_ * 8000 Hz * 64 (+0.23%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_8;
		}
		break;
	case 11025:
		acps = 5622000;
		switch (width) {
		case 16:
			/* 351375 Hz ~= 11025 Hz * 32 (-0.41%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_4;
			break;
		default: /* 32 */
			/* 702750 Hz ~= 11025 Hz * 64 (-0.41%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_2;
		}
		break;
	case 22050:
		acps = 5622000;
		switch (width) {
		case 16:
			/* 702750 Hz ~= 22050 Hz * 32 (-0.41%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_2;
			break;
		default: /* 32 */
			/* 1405500 Hz ~= 22050 Hz * 64 (-0.41%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_1;
		}
		break;
	case 44100:
		acps = 5622000;
		switch (width) {
		case 16:
			/* 1405500 Hz ~= 44100 Hz * 32 (-0.41%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_2;
			break;
		default: /* 32 */
			/* 2811000 Hz ~= 44100 Hz * 64 (-0.41%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_1;
		}
		break;
	case 48000:
		acps = 12235000;
		switch (width) {
		case 16:
			/* 1529375 Hz ~= 48000 Hz * 32 (-0.44%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_2;
			break;
		default: /* 32 */
			/* 3058750 Hz ~= 48000 Hz * 64 (-0.44%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_1;
		}
		break;
	case 96000:
	default:
		acps = 12235000;
		switch (width) {
		case 16:
			/* 3058750 Hz ~= 96000 Hz * 32 (-0.44%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_1;
			break;
		default: /* 32 */
			/* 6117500 Hz ~= 96000 Hz * 64 (-0.44%) */
			acds = PXA_SSP_CLK_AUDIO_DIV_2;
			div4 = PXA_SSP_CLK_SCDB_1;
			break;
		}
		break;
	}

	/* set codec DAI configuration */
	ret = snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_MSB |
			SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBS_CFS);
	if (ret < 0)
		return ret;

	/* set cpu DAI configuration */
	ret = snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_DSP_A |
			SND_SOC_DAIFMT_NB_IF | SND_SOC_DAIFMT_CBS_CFS);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_tdm_slot(cpu_dai, 1, 0, 1, width);
	if (ret < 0)
		return ret;

	/* set audio clock as clock source */
	ret = snd_soc_dai_set_sysclk(cpu_dai, PXA_SSP_CLK_AUDIO, 0,
			SND_SOC_CLOCK_OUT);
	if (ret < 0)
		return ret;

	/* set the SSP audio system clock ACDS divider */
	ret = snd_soc_dai_set_clkdiv(cpu_dai,
			PXA_SSP_AUDIO_DIV_ACDS, acds);
	if (ret < 0)
		return ret;

	/* set the SSP audio system clock SCDB divider4 */
	ret = snd_soc_dai_set_clkdiv(cpu_dai,
			PXA_SSP_AUDIO_DIV_SCDB, div4);
	if (ret < 0)
		return ret;

	/* set SSP audio pll clock */
	ret = snd_soc_dai_set_pll(cpu_dai, 0, 0, acps);
	if (ret < 0)
		return ret;

	return 0;
}