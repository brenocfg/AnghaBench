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
struct s3c24xx_audio_simtec_pdata {scalar_t__* amp_gain; scalar_t__ amp_gpio; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__* amp_gain; scalar_t__ amp_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  gpio_direction_output (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int gpio_request (scalar_t__,char*) ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  spk_unmute_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int attach_gpio_amp(struct device *dev,
			   struct s3c24xx_audio_simtec_pdata *pd)
{
	int ret;

	/* attach gpio amp gain (if any) */
	if (pdata->amp_gain[0] > 0) {
		ret = gpio_request(pd->amp_gain[0], "gpio-amp-gain0");
		if (ret) {
			dev_err(dev, "cannot get amp gpio gain0\n");
			return ret;
		}

		ret = gpio_request(pd->amp_gain[1], "gpio-amp-gain1");
		if (ret) {
			dev_err(dev, "cannot get amp gpio gain1\n");
			gpio_free(pdata->amp_gain[0]);
			return ret;
		}

		gpio_direction_output(pd->amp_gain[0], 0);
		gpio_direction_output(pd->amp_gain[1], 0);
	}

	/* note, curently we assume GPA0 isn't valid amp */
	if (pdata->amp_gpio > 0) {
		ret = gpio_request(pd->amp_gpio, "gpio-amp");
		if (ret) {
			dev_err(dev, "cannot get amp gpio %d (%d)\n",
				pd->amp_gpio, ret);
			goto err_amp;
		}

		/* set the amp off at startup */
		spk_unmute_state(0);
	}

	return 0;

err_amp:
	if (pd->amp_gain[0] > 0) {
		gpio_free(pd->amp_gain[0]);
		gpio_free(pd->amp_gain[1]);
	}

	return ret;
}