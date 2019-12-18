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
struct snd_soc_codec {int* reg_cache; scalar_t__ suspend_bias_level; int /*<<< orphan*/  delayed_work; scalar_t__ bias_level; int /*<<< orphan*/  control_data; int /*<<< orphan*/  (* hw_write ) (int /*<<< orphan*/ ,int*,int) ;} ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ SND_SOC_BIAS_ON ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WM8971_PWR1 ; 
 int WM8971_RESET ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  wm8971_reg ; 
 int /*<<< orphan*/  wm8971_set_bias_level (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8971_workq ; 

__attribute__((used)) static int wm8971_resume(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec = socdev->card->codec;
	int i;
	u8 data[2];
	u16 *cache = codec->reg_cache;
	u16 reg;

	/* Sync reg_cache with the hardware */
	for (i = 0; i < ARRAY_SIZE(wm8971_reg); i++) {
		if (i + 1 == WM8971_RESET)
			continue;
		data[0] = (i << 1) | ((cache[i] >> 8) & 0x0001);
		data[1] = cache[i] & 0x00ff;
		codec->hw_write(codec->control_data, data, 2);
	}

	wm8971_set_bias_level(codec, SND_SOC_BIAS_STANDBY);

	/* charge wm8971 caps */
	if (codec->suspend_bias_level == SND_SOC_BIAS_ON) {
		reg = snd_soc_read(codec, WM8971_PWR1) & 0xfe3e;
		snd_soc_write(codec, WM8971_PWR1, reg | 0x01c0);
		codec->bias_level = SND_SOC_BIAS_ON;
		queue_delayed_work(wm8971_workq, &codec->delayed_work,
			msecs_to_jiffies(1000));
	}

	return 0;
}