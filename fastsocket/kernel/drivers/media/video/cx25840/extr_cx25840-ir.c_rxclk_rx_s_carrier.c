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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX25840_IR_RXCLK_REG ; 
 int /*<<< orphan*/  carrier_freq_to_clock_divider (unsigned int) ; 
 unsigned int clock_divider_to_carrier_freq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int rxclk_rx_s_carrier(struct i2c_client *c,
				       unsigned int freq,
				       u16 *divider)
{
	*divider = carrier_freq_to_clock_divider(freq);
	cx25840_write4(c, CX25840_IR_RXCLK_REG, *divider);
	return clock_divider_to_carrier_freq(*divider);
}