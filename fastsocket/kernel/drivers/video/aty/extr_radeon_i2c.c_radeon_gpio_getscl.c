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
struct radeonfb_info {int dummy; } ;
struct radeon_i2c_chan {int /*<<< orphan*/  ddc_reg; struct radeonfb_info* rinfo; } ;

/* Variables and functions */
 int INREG (int /*<<< orphan*/ ) ; 
 int VGA_DDC_CLK_INPUT ; 

__attribute__((used)) static int radeon_gpio_getscl(void* data)
{
	struct radeon_i2c_chan 	*chan = data;
	struct radeonfb_info	*rinfo = chan->rinfo;
	u32			val;
	
	val = INREG(chan->ddc_reg);

	return (val & VGA_DDC_CLK_INPUT) ? 1 : 0;
}