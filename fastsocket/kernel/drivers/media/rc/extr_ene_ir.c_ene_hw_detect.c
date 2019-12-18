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
struct ene_device {int pll_freq; int rx_period_adjust; scalar_t__ hw_revision; int hw_use_gpio_0a; int hw_learning_and_tx_capable; int hw_extra_buffer; int hw_fan_input; } ;

/* Variables and functions */
 int ENE_DEFAULT_PLL_FREQ ; 
 scalar_t__ ENE_DEFAULT_SAMPLE_PERIOD ; 
 int /*<<< orphan*/  ENE_ECHV ; 
 int /*<<< orphan*/  ENE_ECSTS ; 
 int /*<<< orphan*/  ENE_ECSTS_RSRVD ; 
 int /*<<< orphan*/  ENE_ECVER_MAJOR ; 
 int /*<<< orphan*/  ENE_ECVER_MINOR ; 
 int /*<<< orphan*/  ENE_FW1 ; 
 int ENE_FW1_HAS_EXTRA_BUF ; 
 int /*<<< orphan*/  ENE_FW2 ; 
 int ENE_FW2_FAN_INPUT ; 
 int ENE_FW2_GP0A ; 
 int ENE_FW2_LEARNING ; 
 scalar_t__ ENE_HW_B ; 
 scalar_t__ ENE_HW_C ; 
 scalar_t__ ENE_HW_D ; 
 int /*<<< orphan*/  ENE_HW_VER_OLD ; 
 int /*<<< orphan*/  ENE_PLLFRH ; 
 int /*<<< orphan*/  ENE_PLLFRL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ene_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_notice (char*,...) ; 
 int ene_read_reg (struct ene_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_set_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_warn (char*) ; 
 scalar_t__ sample_period ; 

__attribute__((used)) static int ene_hw_detect(struct ene_device *dev)
{
	u8 chip_major, chip_minor;
	u8 hw_revision, old_ver;
	u8 fw_reg2, fw_reg1;

	ene_clear_reg_mask(dev, ENE_ECSTS, ENE_ECSTS_RSRVD);
	chip_major = ene_read_reg(dev, ENE_ECVER_MAJOR);
	chip_minor = ene_read_reg(dev, ENE_ECVER_MINOR);
	ene_set_reg_mask(dev, ENE_ECSTS, ENE_ECSTS_RSRVD);

	hw_revision = ene_read_reg(dev, ENE_ECHV);
	old_ver = ene_read_reg(dev, ENE_HW_VER_OLD);

	dev->pll_freq = (ene_read_reg(dev, ENE_PLLFRH) << 4) +
		(ene_read_reg(dev, ENE_PLLFRL) >> 4);

	if (sample_period != ENE_DEFAULT_SAMPLE_PERIOD)
		dev->rx_period_adjust =
			dev->pll_freq == ENE_DEFAULT_PLL_FREQ ? 2 : 4;

	if (hw_revision == 0xFF) {
		ene_warn("device seems to be disabled");
		ene_warn("send a mail to lirc-list@lists.sourceforge.net");
		ene_warn("please attach output of acpidump and dmidecode");
		return -ENODEV;
	}

	ene_notice("chip is 0x%02x%02x - kbver = 0x%02x, rev = 0x%02x",
		chip_major, chip_minor, old_ver, hw_revision);

	ene_notice("PLL freq = %d", dev->pll_freq);

	if (chip_major == 0x33) {
		ene_warn("chips 0x33xx aren't supported");
		return -ENODEV;
	}

	if (chip_major == 0x39 && chip_minor == 0x26 && hw_revision == 0xC0) {
		dev->hw_revision = ENE_HW_C;
		ene_notice("KB3926C detected");
	} else if (old_ver == 0x24 && hw_revision == 0xC0) {
		dev->hw_revision = ENE_HW_B;
		ene_notice("KB3926B detected");
	} else {
		dev->hw_revision = ENE_HW_D;
		ene_notice("KB3926D or higher detected");
	}

	/* detect features hardware supports */
	if (dev->hw_revision < ENE_HW_C)
		return 0;

	fw_reg1 = ene_read_reg(dev, ENE_FW1);
	fw_reg2 = ene_read_reg(dev, ENE_FW2);

	ene_notice("Firmware regs: %02x %02x", fw_reg1, fw_reg2);

	dev->hw_use_gpio_0a = !!(fw_reg2 & ENE_FW2_GP0A);
	dev->hw_learning_and_tx_capable = !!(fw_reg2 & ENE_FW2_LEARNING);
	dev->hw_extra_buffer = !!(fw_reg1 & ENE_FW1_HAS_EXTRA_BUF);

	if (dev->hw_learning_and_tx_capable)
		dev->hw_fan_input = !!(fw_reg2 & ENE_FW2_FAN_INPUT);

	ene_notice("Hardware features:");

	if (dev->hw_learning_and_tx_capable) {
		ene_notice("* Supports transmitting & learning mode");
		ene_notice("   This feature is rare and therefore,");
		ene_notice("   you are welcome to test it,");
		ene_notice("   and/or contact the author via:");
		ene_notice("   lirc-list@lists.sourceforge.net");
		ene_notice("   or maximlevitsky@gmail.com");

		ene_notice("* Uses GPIO %s for IR raw input",
			dev->hw_use_gpio_0a ? "40" : "0A");

		if (dev->hw_fan_input)
			ene_notice("* Uses unused fan feedback input as source"
					" of demodulated IR data");
	}

	if (!dev->hw_fan_input)
		ene_notice("* Uses GPIO %s for IR demodulated input",
			dev->hw_use_gpio_0a ? "0A" : "40");

	if (dev->hw_extra_buffer)
		ene_notice("* Uses new style input buffer");
	return 0;
}