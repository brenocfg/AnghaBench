#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wm97xx {int /*<<< orphan*/  codec_mutex; } ;
typedef  enum wm97xx_gpio_wake { ____Placeholder_wm97xx_gpio_wake } wm97xx_gpio_wake ;
typedef  enum wm97xx_gpio_sticky { ____Placeholder_wm97xx_gpio_sticky } wm97xx_gpio_sticky ;
typedef  enum wm97xx_gpio_pol { ____Placeholder_wm97xx_gpio_pol } wm97xx_gpio_pol ;
typedef  enum wm97xx_gpio_dir { ____Placeholder_wm97xx_gpio_dir } wm97xx_gpio_dir ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_GPIO_CFG ; 
 int /*<<< orphan*/  AC97_GPIO_POLARITY ; 
 int /*<<< orphan*/  AC97_GPIO_STICKY ; 
 int /*<<< orphan*/  AC97_GPIO_WAKEUP ; 
 int WM97XX_GPIO_IN ; 
 int WM97XX_GPIO_POL_HIGH ; 
 int WM97XX_GPIO_STICKY ; 
 int WM97XX_GPIO_WAKE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm97xx_reg_read (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wm97xx_config_gpio(struct wm97xx *wm, u32 gpio, enum wm97xx_gpio_dir dir,
		   enum wm97xx_gpio_pol pol, enum wm97xx_gpio_sticky sticky,
		   enum wm97xx_gpio_wake wake)
{
	u16 reg;

	mutex_lock(&wm->codec_mutex);
	reg = wm97xx_reg_read(wm, AC97_GPIO_POLARITY);

	if (pol == WM97XX_GPIO_POL_HIGH)
		reg |= gpio;
	else
		reg &= ~gpio;

	wm97xx_reg_write(wm, AC97_GPIO_POLARITY, reg);
	reg = wm97xx_reg_read(wm, AC97_GPIO_STICKY);

	if (sticky == WM97XX_GPIO_STICKY)
		reg |= gpio;
	else
		reg &= ~gpio;

	wm97xx_reg_write(wm, AC97_GPIO_STICKY, reg);
	reg = wm97xx_reg_read(wm, AC97_GPIO_WAKEUP);

	if (wake == WM97XX_GPIO_WAKE)
		reg |= gpio;
	else
		reg &= ~gpio;

	wm97xx_reg_write(wm, AC97_GPIO_WAKEUP, reg);
	reg = wm97xx_reg_read(wm, AC97_GPIO_CFG);

	if (dir == WM97XX_GPIO_IN)
		reg |= gpio;
	else
		reg &= ~gpio;

	wm97xx_reg_write(wm, AC97_GPIO_CFG, reg);
	mutex_unlock(&wm->codec_mutex);
}