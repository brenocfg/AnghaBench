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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOWAKEUP_CFG ; 
 int /*<<< orphan*/  AUX_CTRL ; 
 int /*<<< orphan*/  AUX_CTRL_FORCE_PCIE_CLK ; 
 int /*<<< orphan*/  AUX_CTRL_WAKE_PCIE_EN ; 
 int EBUSY ; 
 int /*<<< orphan*/  H2M_BBP_AGENT ; 
 int /*<<< orphan*/  H2M_INT_SRC ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR ; 
 int /*<<< orphan*/  MCU_BOOT_SIGNAL ; 
 int /*<<< orphan*/  PBF_SYS_CTRL ; 
 int /*<<< orphan*/  PBF_SYS_CTRL_READY ; 
 int /*<<< orphan*/  PWR_PIN_CFG ; 
 unsigned int REGISTER_BUSY_COUNT ; 
 int /*<<< orphan*/  RT3290 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  RT5390 ; 
 int /*<<< orphan*/  RT5392 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2800_disable_wpdma (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_drv_write_firmware (struct rt2x00_dev*,int /*<<< orphan*/  const*,size_t const) ; 
 int rt2800_enable_wlan_rt3290 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_mcu_request (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rt2800_wait_csr_ready (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 scalar_t__ rt2x00_get_field32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_is_pci (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 

int rt2800_load_firmware(struct rt2x00_dev *rt2x00dev,
			 const u8 *data, const size_t len)
{
	unsigned int i;
	u32 reg;
	int retval;

	if (rt2x00_rt(rt2x00dev, RT3290)) {
		retval = rt2800_enable_wlan_rt3290(rt2x00dev);
		if (retval)
			return -EBUSY;
	}

	/*
	 * If driver doesn't wake up firmware here,
	 * rt2800_load_firmware will hang forever when interface is up again.
	 */
	rt2800_register_write(rt2x00dev, AUTOWAKEUP_CFG, 0x00000000);

	/*
	 * Wait for stable hardware.
	 */
	if (rt2800_wait_csr_ready(rt2x00dev))
		return -EBUSY;

	if (rt2x00_is_pci(rt2x00dev)) {
		if (rt2x00_rt(rt2x00dev, RT3290) ||
		    rt2x00_rt(rt2x00dev, RT3572) ||
		    rt2x00_rt(rt2x00dev, RT5390) ||
		    rt2x00_rt(rt2x00dev, RT5392)) {
			rt2800_register_read(rt2x00dev, AUX_CTRL, &reg);
			rt2x00_set_field32(&reg, AUX_CTRL_FORCE_PCIE_CLK, 1);
			rt2x00_set_field32(&reg, AUX_CTRL_WAKE_PCIE_EN, 1);
			rt2800_register_write(rt2x00dev, AUX_CTRL, reg);
		}
		rt2800_register_write(rt2x00dev, PWR_PIN_CFG, 0x00000002);
	}

	rt2800_disable_wpdma(rt2x00dev);

	/*
	 * Write firmware to the device.
	 */
	rt2800_drv_write_firmware(rt2x00dev, data, len);

	/*
	 * Wait for device to stabilize.
	 */
	for (i = 0; i < REGISTER_BUSY_COUNT; i++) {
		rt2800_register_read(rt2x00dev, PBF_SYS_CTRL, &reg);
		if (rt2x00_get_field32(reg, PBF_SYS_CTRL_READY))
			break;
		msleep(1);
	}

	if (i == REGISTER_BUSY_COUNT) {
		rt2x00_err(rt2x00dev, "PBF system register not ready\n");
		return -EBUSY;
	}

	/*
	 * Disable DMA, will be reenabled later when enabling
	 * the radio.
	 */
	rt2800_disable_wpdma(rt2x00dev);

	/*
	 * Initialize firmware.
	 */
	rt2800_register_write(rt2x00dev, H2M_BBP_AGENT, 0);
	rt2800_register_write(rt2x00dev, H2M_MAILBOX_CSR, 0);
	if (rt2x00_is_usb(rt2x00dev)) {
		rt2800_register_write(rt2x00dev, H2M_INT_SRC, 0);
		rt2800_mcu_request(rt2x00dev, MCU_BOOT_SIGNAL, 0, 0, 0);
	}
	msleep(1);

	return 0;
}