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
struct s6000_i2s_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S6_I2S_DISABLE_IF ; 
 int /*<<< orphan*/  S6_I2S_ENABLE (int) ; 
 int /*<<< orphan*/  s6_i2s_write_reg (struct s6000_i2s_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s6000_i2s_stop_channel(struct s6000_i2s_dev *dev, int channel)
{
	s6_i2s_write_reg(dev, S6_I2S_ENABLE(channel), S6_I2S_DISABLE_IF);
}