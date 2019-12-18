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
 int /*<<< orphan*/  S6_I2S_INTERRUPT_CLEAR ; 
 int /*<<< orphan*/  S6_I2S_INTERRUPT_RAW ; 
 unsigned int S6_I2S_INT_ALIGNMENT ; 
 unsigned int S6_I2S_INT_OVERRUN ; 
 unsigned int S6_I2S_INT_UNDERRUN ; 
 unsigned int s6_i2s_read_reg (struct s6000_i2s_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6_i2s_write_reg (struct s6000_i2s_dev*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int s6000_i2s_int_sources(struct s6000_i2s_dev *dev)
{
	unsigned int pending;
	pending = s6_i2s_read_reg(dev, S6_I2S_INTERRUPT_RAW);
	pending &= S6_I2S_INT_ALIGNMENT |
		   S6_I2S_INT_UNDERRUN |
		   S6_I2S_INT_OVERRUN;
	s6_i2s_write_reg(dev, S6_I2S_INTERRUPT_CLEAR, pending);

	return pending;
}