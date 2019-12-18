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
 int /*<<< orphan*/  aic3x_read (struct snd_soc_codec*,int,int*) ; 

int aic3x_get_gpio(struct snd_soc_codec *codec, int gpio)
{
	u8 reg = gpio ? AIC3X_GPIO2_REG : AIC3X_GPIO1_REG;
	u8 val, bit = gpio ? 2: 1;

	aic3x_read(codec, reg, &val);
	return (val >> bit) & 1;
}