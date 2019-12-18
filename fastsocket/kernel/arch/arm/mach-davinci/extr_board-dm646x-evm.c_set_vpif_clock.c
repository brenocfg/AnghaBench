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

/* Variables and functions */
 int ENXIO ; 
 unsigned int VCH2CLK_AUXCLK ; 
 unsigned int VCH2CLK_MASK ; 
 unsigned int VCH2CLK_SYSCLK8 ; 
 unsigned int VCH3CLK_AUXCLK ; 
 unsigned int VCH3CLK_MASK ; 
 unsigned int VCH3CLK_SYSCLK8 ; 
 unsigned int VIDCH2CLK ; 
 unsigned int VIDCH3CLK ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpld_client ; 
 int i2c_smbus_read_byte (int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vpif_reg_lock ; 
 int /*<<< orphan*/  vpif_vidclkctl_reg ; 
 int /*<<< orphan*/  vpif_vsclkdis_reg ; 

__attribute__((used)) static int set_vpif_clock(int mux_mode, int hd)
{
	unsigned long flags;
	unsigned int value;
	int val = 0;
	int err = 0;

	if (!vpif_vidclkctl_reg || !vpif_vsclkdis_reg || !cpld_client)
		return -ENXIO;

	/* disable the clock */
	spin_lock_irqsave(&vpif_reg_lock, flags);
	value = __raw_readl(vpif_vsclkdis_reg);
	value |= (VIDCH3CLK | VIDCH2CLK);
	__raw_writel(value, vpif_vsclkdis_reg);
	spin_unlock_irqrestore(&vpif_reg_lock, flags);

	val = i2c_smbus_read_byte(cpld_client);
	if (val < 0)
		return val;

	if (mux_mode == 1)
		val &= ~0x40;
	else
		val |= 0x40;

	err = i2c_smbus_write_byte(cpld_client, val);
	if (err)
		return err;

	value = __raw_readl(vpif_vidclkctl_reg);
	value &= ~(VCH2CLK_MASK);
	value &= ~(VCH3CLK_MASK);

	if (hd >= 1)
		value |= (VCH2CLK_SYSCLK8 | VCH3CLK_SYSCLK8);
	else
		value |= (VCH2CLK_AUXCLK | VCH3CLK_AUXCLK);

	__raw_writel(value, vpif_vidclkctl_reg);

	spin_lock_irqsave(&vpif_reg_lock, flags);
	value = __raw_readl(vpif_vsclkdis_reg);
	/* enable the clock */
	value &= ~(VIDCH3CLK | VIDCH2CLK);
	__raw_writel(value, vpif_vsclkdis_reg);
	spin_unlock_irqrestore(&vpif_reg_lock, flags);

	return 0;
}