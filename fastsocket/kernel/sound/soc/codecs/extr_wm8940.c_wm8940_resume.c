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
typedef  int u8 ;
typedef  int u16 ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_codec {int* reg_cache; int (* hw_write ) (int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  suspend_bias_level; int /*<<< orphan*/  control_data; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int stub1 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  wm8940_reg_defaults ; 
 int wm8940_set_bias_level (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8940_resume(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec = socdev->card->codec;
	int i;
	int ret;
	u8 data[3];
	u16 *cache = codec->reg_cache;

	/* Sync reg_cache with the hardware
	 * Could use auto incremented writes to speed this up
	 */
	for (i = 0; i < ARRAY_SIZE(wm8940_reg_defaults); i++) {
		data[0] = i;
		data[1] = (cache[i] & 0xFF00) >> 8;
		data[2] = cache[i] & 0x00FF;
		ret = codec->hw_write(codec->control_data, data, 3);
		if (ret < 0)
			goto error_ret;
		else if (ret != 3) {
			ret = -EIO;
			goto error_ret;
		}
	}
	ret = wm8940_set_bias_level(codec, SND_SOC_BIAS_STANDBY);
	if (ret)
		goto error_ret;
	ret = wm8940_set_bias_level(codec, codec->suspend_bias_level);

error_ret:
	return ret;
}