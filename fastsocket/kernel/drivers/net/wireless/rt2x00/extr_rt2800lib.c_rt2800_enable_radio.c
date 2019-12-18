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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_LED_ACT_CONF ; 
 int /*<<< orphan*/  EEPROM_LED_AG_CONF ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY ; 
 int EIO ; 
 int /*<<< orphan*/  H2M_BBP_AGENT ; 
 int /*<<< orphan*/  H2M_INT_SRC ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR ; 
 int /*<<< orphan*/  MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_ENABLE_RX ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  MCU_BOOT_SIGNAL ; 
 int /*<<< orphan*/  MCU_CURRENT ; 
 int /*<<< orphan*/  MCU_LED_ACT_CONF ; 
 int /*<<< orphan*/  MCU_LED_AG_CONF ; 
 int /*<<< orphan*/  MCU_LED_LED_POLARITY ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3071 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_ENABLE_RX_DMA ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_ENABLE_TX_DMA ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_WP_DMA_BURST_SIZE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rt2800_init_bbp (struct rt2x00_dev*) ; 
 scalar_t__ rt2800_init_registers (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_mcu_request (struct rt2x00_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2800_wait_wpdma_ready (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

int rt2800_enable_radio(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;
	u16 word;

	/*
	 * Initialize all registers.
	 */
	if (unlikely(rt2800_wait_wpdma_ready(rt2x00dev) ||
		     rt2800_init_registers(rt2x00dev)))
		return -EIO;

	/*
	 * Send signal to firmware during boot time.
	 */
	rt2800_register_write(rt2x00dev, H2M_BBP_AGENT, 0);
	rt2800_register_write(rt2x00dev, H2M_MAILBOX_CSR, 0);
	if (rt2x00_is_usb(rt2x00dev)) {
		rt2800_register_write(rt2x00dev, H2M_INT_SRC, 0);
		rt2800_mcu_request(rt2x00dev, MCU_BOOT_SIGNAL, 0, 0, 0);
	}
	msleep(1);

	if (unlikely(rt2800_init_bbp(rt2x00dev)))
		return -EIO;

	rt2800_init_rfcsr(rt2x00dev);

	if (rt2x00_is_usb(rt2x00dev) &&
	    (rt2x00_rt(rt2x00dev, RT3070) ||
	     rt2x00_rt(rt2x00dev, RT3071) ||
	     rt2x00_rt(rt2x00dev, RT3572))) {
		udelay(200);
		rt2800_mcu_request(rt2x00dev, MCU_CURRENT, 0, 0, 0);
		udelay(10);
	}

	/*
	 * Enable RX.
	 */
	rt2800_register_read(rt2x00dev, MAC_SYS_CTRL, &reg);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_TX, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 0);
	rt2800_register_write(rt2x00dev, MAC_SYS_CTRL, reg);

	udelay(50);

	rt2800_register_read(rt2x00dev, WPDMA_GLO_CFG, &reg);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_TX_DMA, 1);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_RX_DMA, 1);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_WP_DMA_BURST_SIZE, 2);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_WRITEBACK_DONE, 1);
	rt2800_register_write(rt2x00dev, WPDMA_GLO_CFG, reg);

	rt2800_register_read(rt2x00dev, MAC_SYS_CTRL, &reg);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_TX, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 1);
	rt2800_register_write(rt2x00dev, MAC_SYS_CTRL, reg);

	/*
	 * Initialize LED control
	 */
	rt2x00_eeprom_read(rt2x00dev, EEPROM_LED_AG_CONF, &word);
	rt2800_mcu_request(rt2x00dev, MCU_LED_AG_CONF, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	rt2x00_eeprom_read(rt2x00dev, EEPROM_LED_ACT_CONF, &word);
	rt2800_mcu_request(rt2x00dev, MCU_LED_ACT_CONF, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	rt2x00_eeprom_read(rt2x00dev, EEPROM_LED_POLARITY, &word);
	rt2800_mcu_request(rt2x00dev, MCU_LED_LED_POLARITY, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	return 0;
}