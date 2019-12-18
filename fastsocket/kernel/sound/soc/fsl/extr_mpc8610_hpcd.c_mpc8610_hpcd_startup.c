#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_3__* socdev; TYPE_1__* dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {TYPE_5__* pcm; struct snd_soc_pcm_runtime* private_data; } ;
struct mpc8610_hpcd_data {int /*<<< orphan*/  codec_clk_direction; int /*<<< orphan*/  clk_frequency; int /*<<< orphan*/  cpu_clk_direction; int /*<<< orphan*/  dai_format; } ;
struct TYPE_10__ {TYPE_4__* card; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {TYPE_2__* dev; } ;
struct TYPE_7__ {struct mpc8610_hpcd_data* platform_data; } ;
struct TYPE_6__ {struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_soc_dai_set_fmt (struct snd_soc_dai*,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc8610_hpcd_startup(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->dai->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	struct mpc8610_hpcd_data *machine_data =
		rtd->socdev->dev->platform_data;
	int ret = 0;

	/* Tell the CPU driver what the serial protocol is. */
	ret = snd_soc_dai_set_fmt(cpu_dai, machine_data->dai_format);
	if (ret < 0) {
		dev_err(substream->pcm->card->dev,
			"could not set CPU driver audio format\n");
		return ret;
	}

	/* Tell the codec driver what the serial protocol is. */
	ret = snd_soc_dai_set_fmt(codec_dai, machine_data->dai_format);
	if (ret < 0) {
		dev_err(substream->pcm->card->dev,
			"could not set codec driver audio format\n");
		return ret;
	}

	/*
	 * Tell the CPU driver what the clock frequency is, and whether it's a
	 * slave or master.
	 */
	ret = snd_soc_dai_set_sysclk(cpu_dai, 0,
					machine_data->clk_frequency,
					machine_data->cpu_clk_direction);
	if (ret < 0) {
		dev_err(substream->pcm->card->dev,
			"could not set CPU driver clock parameters\n");
		return ret;
	}

	/*
	 * Tell the codec driver what the MCLK frequency is, and whether it's
	 * a slave or master.
	 */
	ret = snd_soc_dai_set_sysclk(codec_dai, 0,
					machine_data->clk_frequency,
					machine_data->codec_clk_direction);
	if (ret < 0) {
		dev_err(substream->pcm->card->dev,
			"could not set codec driver clock params\n");
		return ret;
	}

	return 0;
}