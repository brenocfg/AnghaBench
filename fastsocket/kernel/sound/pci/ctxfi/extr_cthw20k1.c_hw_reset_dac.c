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
struct hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO ; 
 scalar_t__ hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 unsigned int hw_read_pci (struct hw*,int) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_write_pci (struct hw*,int,int) ; 
 int /*<<< orphan*/  i2c_lock (struct hw*) ; 
 scalar_t__ i2c_unlock (struct hw*) ; 
 int /*<<< orphan*/  i2c_write (struct hw*,int,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int hw_reset_dac(struct hw *hw)
{
	u32 i;
	u16 gpioorg;
	unsigned int ret;

	if (i2c_unlock(hw))
		return -1;

	do {
		ret = hw_read_pci(hw, 0xEC);
	} while (!(ret & 0x800000));
	hw_write_pci(hw, 0xEC, 0x05);  /* write to i2c status control */

	/* To be effective, need to reset the DAC twice. */
	for (i = 0; i < 2;  i++) {
		/* set gpio */
		mdelay(100);
		gpioorg = (u16)hw_read_20kx(hw, GPIO);
		gpioorg &= 0xfffd;
		hw_write_20kx(hw, GPIO, gpioorg);
		mdelay(1);
		hw_write_20kx(hw, GPIO, gpioorg | 0x2);
	}

	i2c_write(hw, 0x00180080, 0x01, 0x80);
	i2c_write(hw, 0x00180080, 0x02, 0x10);

	i2c_lock(hw);

	return 0;
}