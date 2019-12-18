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
struct twl4030_gpio_platform_data {int mmc_cd; } ;
struct gpio_chip {TYPE_1__* dev; } ;
struct TYPE_2__ {struct twl4030_gpio_platform_data* platform_data; } ;

/* Variables and functions */
 int LEDEN_LEDAEXT ; 
 int LEDEN_LEDAON ; 
 int LEDEN_LEDAPWM ; 
 int LEDEN_PWM_LENGTHA ; 
 int MASK_GPIO_CTRL_GPIO_ON ; 
 int /*<<< orphan*/  REG_GPIO_CTRL ; 
 unsigned int TWL4030_GPIO_MAX ; 
 int /*<<< orphan*/  TWL4030_LED_LEDEN ; 
 int TWL4030_MODULE_LED ; 
 int TWL4030_MODULE_PWMA ; 
 int TWL4030_MODULE_PWMB ; 
 int /*<<< orphan*/  TWL4030_PWMx_PWMxOFF ; 
 int /*<<< orphan*/  TWL4030_PWMx_PWMxON ; 
 int cached_leden ; 
 int /*<<< orphan*/  gpio_lock ; 
 int gpio_twl4030_write (int /*<<< orphan*/ ,int) ; 
 int gpio_usage_count ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int twl4030_i2c_read_u8 (int,int*,int /*<<< orphan*/ ) ; 
 int twl4030_i2c_write_u8 (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl_request(struct gpio_chip *chip, unsigned offset)
{
	int status = 0;

	mutex_lock(&gpio_lock);

	/* Support the two LED outputs as output-only GPIOs. */
	if (offset >= TWL4030_GPIO_MAX) {
		u8	ledclr_mask = LEDEN_LEDAON | LEDEN_LEDAEXT
				| LEDEN_LEDAPWM | LEDEN_PWM_LENGTHA;
		u8	module = TWL4030_MODULE_PWMA;

		offset -= TWL4030_GPIO_MAX;
		if (offset) {
			ledclr_mask <<= 1;
			module = TWL4030_MODULE_PWMB;
		}

		/* initialize PWM to always-drive */
		status = twl4030_i2c_write_u8(module, 0x7f,
				TWL4030_PWMx_PWMxOFF);
		if (status < 0)
			goto done;
		status = twl4030_i2c_write_u8(module, 0x7f,
				TWL4030_PWMx_PWMxON);
		if (status < 0)
			goto done;

		/* init LED to not-driven (high) */
		module = TWL4030_MODULE_LED;
		status = twl4030_i2c_read_u8(module, &cached_leden,
				TWL4030_LED_LEDEN);
		if (status < 0)
			goto done;
		cached_leden &= ~ledclr_mask;
		status = twl4030_i2c_write_u8(module, cached_leden,
				TWL4030_LED_LEDEN);
		if (status < 0)
			goto done;

		status = 0;
		goto done;
	}

	/* on first use, turn GPIO module "on" */
	if (!gpio_usage_count) {
		struct twl4030_gpio_platform_data *pdata;
		u8 value = MASK_GPIO_CTRL_GPIO_ON;

		/* optionally have the first two GPIOs switch vMMC1
		 * and vMMC2 power supplies based on card presence.
		 */
		pdata = chip->dev->platform_data;
		value |= pdata->mmc_cd & 0x03;

		status = gpio_twl4030_write(REG_GPIO_CTRL, value);
	}

	if (!status)
		gpio_usage_count |= (0x1 << offset);

done:
	mutex_unlock(&gpio_lock);
	return status;
}