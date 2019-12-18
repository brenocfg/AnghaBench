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
typedef  int u8 ;
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int AIC3X_GPIO1_REG ; 
 int AIC3X_GPIO2_REG ; 
 int aic3x_read_reg_cache (struct snd_soc_codec*,int) ; 
 int /*<<< orphan*/  aic3x_write (struct snd_soc_codec*,int,int) ; 

void aic3x_set_gpio(struct snd_soc_codec *codec, int gpio, int state)
{
	u8 reg = gpio ? AIC3X_GPIO2_REG : AIC3X_GPIO1_REG;
	u8 bit = gpio ? 3: 0;
	u8 val = aic3x_read_reg_cache(codec, reg) & ~(1 << bit);
	aic3x_write(codec, reg, val | (!!state << bit));
}