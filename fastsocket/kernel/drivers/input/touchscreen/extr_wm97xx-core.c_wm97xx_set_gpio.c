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
typedef  int u32 ;
typedef  int u16 ;
struct wm97xx {scalar_t__ id; scalar_t__ variant; int /*<<< orphan*/  codec_mutex; } ;
typedef  enum wm97xx_gpio_status { ____Placeholder_wm97xx_gpio_status } wm97xx_gpio_status ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_GPIO_STATUS ; 
 scalar_t__ WM9712_ID2 ; 
 int WM97XX_GPIO_HIGH ; 
 scalar_t__ WM97xx_WM1613 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wm97xx_reg_read (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int) ; 

void wm97xx_set_gpio(struct wm97xx *wm, u32 gpio,
				enum wm97xx_gpio_status status)
{
	u16 reg;

	mutex_lock(&wm->codec_mutex);
	reg = wm97xx_reg_read(wm, AC97_GPIO_STATUS);

	if (status & WM97XX_GPIO_HIGH)
		reg |= gpio;
	else
		reg &= ~gpio;

	if (wm->id == WM9712_ID2 && wm->variant != WM97xx_WM1613)
		wm97xx_reg_write(wm, AC97_GPIO_STATUS, reg << 1);
	else
		wm97xx_reg_write(wm, AC97_GPIO_STATUS, reg);
	mutex_unlock(&wm->codec_mutex);
}