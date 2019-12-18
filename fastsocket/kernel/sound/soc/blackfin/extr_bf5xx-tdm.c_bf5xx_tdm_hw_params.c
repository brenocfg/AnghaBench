#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_6__ {int tcr2; int rcr2; int configured; int /*<<< orphan*/  tcr1; int /*<<< orphan*/  rcr1; } ;
struct TYPE_5__ {int wdsize; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 TYPE_4__ bf5xx_tdm ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sport_config_rx (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sport_config_tx (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sport_handle ; 

__attribute__((used)) static int bf5xx_tdm_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params,
	struct snd_soc_dai *dai)
{
	int ret = 0;

	bf5xx_tdm.tcr2 &= ~0x1f;
	bf5xx_tdm.rcr2 &= ~0x1f;
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S32_LE:
		bf5xx_tdm.tcr2 |= 31;
		bf5xx_tdm.rcr2 |= 31;
		sport_handle->wdsize = 4;
		break;
		/* at present, we only support 32bit transfer */
	default:
		pr_err("not supported PCM format yet\n");
		return -EINVAL;
		break;
	}

	if (!bf5xx_tdm.configured) {
		/*
		 * TX and RX are not independent,they are enabled at the
		 * same time, even if only one side is running. So, we
		 * need to configure both of them at the time when the first
		 * stream is opened.
		 *
		 * CPU DAI:slave mode.
		 */
		ret = sport_config_rx(sport_handle, bf5xx_tdm.rcr1,
			bf5xx_tdm.rcr2, 0, 0);
		if (ret) {
			pr_err("SPORT is busy!\n");
			return -EBUSY;
		}

		ret = sport_config_tx(sport_handle, bf5xx_tdm.tcr1,
			bf5xx_tdm.tcr2, 0, 0);
		if (ret) {
			pr_err("SPORT is busy!\n");
			return -EBUSY;
		}

		bf5xx_tdm.configured = 1;
	}

	return 0;
}