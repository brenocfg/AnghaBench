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
struct snd_soc_dai {struct s6000_i2s_dev* private_data; } ;
struct s6000_i2s_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int S6_I2S_DIV_MASK ; 
 int /*<<< orphan*/  S6_I2S_INTERFACE_CFG (int) ; 
 int /*<<< orphan*/  s6_i2s_mod_reg (struct s6000_i2s_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int s6000_i2s_set_clkdiv(struct snd_soc_dai *dai, int div_id, int div)
{
	struct s6000_i2s_dev *dev = dai->private_data;

	if (!div || (div & 1) || div > (S6_I2S_DIV_MASK + 1) * 2)
		return -EINVAL;

	s6_i2s_mod_reg(dev, S6_I2S_INTERFACE_CFG(div_id),
		       S6_I2S_DIV_MASK, div / 2 - 1);
	return 0;
}