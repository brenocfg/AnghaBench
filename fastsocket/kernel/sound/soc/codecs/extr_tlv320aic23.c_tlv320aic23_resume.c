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
typedef  scalar_t__ u16 ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_codec {int /*<<< orphan*/  suspend_bias_level; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 scalar_t__ TLV320AIC23_RESET ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ tlv320aic23_read_reg_cache (struct snd_soc_codec*,scalar_t__) ; 
 int /*<<< orphan*/  tlv320aic23_set_bias_level (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlv320aic23_write (struct snd_soc_codec*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int tlv320aic23_resume(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec = socdev->card->codec;
	u16 reg;

	/* Sync reg_cache with the hardware */
	for (reg = 0; reg < TLV320AIC23_RESET; reg++) {
		u16 val = tlv320aic23_read_reg_cache(codec, reg);
		tlv320aic23_write(codec, reg, val);
	}

	tlv320aic23_set_bias_level(codec, SND_SOC_BIAS_STANDBY);
	tlv320aic23_set_bias_level(codec, codec->suspend_bias_level);

	return 0;
}