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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rt2x00_dev {int /*<<< orphan*/  eeprom; } ;
struct eeprom_93cx6 {scalar_t__ reg_chip_select; scalar_t__ reg_data_clock; scalar_t__ reg_data_out; scalar_t__ reg_data_in; int /*<<< orphan*/  width; int /*<<< orphan*/  register_write; int /*<<< orphan*/  register_read; struct rt2x00_dev* data; } ;
typedef  int s8 ;

/* Variables and functions */
 int ANTENNA_B ; 
 int /*<<< orphan*/  E2PROM_CSR ; 
 int /*<<< orphan*/  E2PROM_CSR_TYPE_93C46 ; 
 int /*<<< orphan*/  EEPROM_ANTENNA ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_DYN_TXAGC ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_FRAME_TYPE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_HARDWARE_RADIO ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_NUM ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RF_TYPE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_TX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_BASE ; 
 int /*<<< orphan*/  EEPROM_FREQ ; 
 int /*<<< orphan*/  EEPROM_FREQ_OFFSET ; 
 int /*<<< orphan*/  EEPROM_FREQ_SEQ ; 
 int /*<<< orphan*/  EEPROM_LED ; 
 int /*<<< orphan*/  EEPROM_LED_LED_MODE ; 
 int /*<<< orphan*/  EEPROM_MAC_ADDR_0 ; 
 int /*<<< orphan*/  EEPROM_NIC ; 
 int /*<<< orphan*/  EEPROM_NIC_CARDBUS_ACCEL ; 
 int /*<<< orphan*/  EEPROM_NIC_ENABLE_DIVERSITY ; 
 int /*<<< orphan*/  EEPROM_NIC_EXTERNAL_LNA_A ; 
 int /*<<< orphan*/  EEPROM_NIC_EXTERNAL_LNA_BG ; 
 int /*<<< orphan*/  EEPROM_NIC_RX_FIXED ; 
 int /*<<< orphan*/  EEPROM_NIC_TX_DIVERSITY ; 
 int /*<<< orphan*/  EEPROM_NIC_TX_FIXED ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_A ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_A_1 ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_A_2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_BG ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_BG_1 ; 
 int /*<<< orphan*/  EEPROM_RSSI_OFFSET_BG_2 ; 
 int EEPROM_SIZE ; 
 int LED_MODE_DEFAULT ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C46 ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C66 ; 
 int RF5225 ; 
 int /*<<< orphan*/  eeprom_93cx6_multiread (struct eeprom_93cx6*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rt2x00_eeprom_addr (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_eeprom_dbg (struct rt2x00_dev*,char*,int) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt2x00_eeprom_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt61pci_eepromregister_read ; 
 int /*<<< orphan*/  rt61pci_eepromregister_write ; 

__attribute__((used)) static int rt61pci_validate_eeprom(struct rt2x00_dev *rt2x00dev)
{
	struct eeprom_93cx6 eeprom;
	u32 reg;
	u16 word;
	u8 *mac;
	s8 value;

	rt2x00mmio_register_read(rt2x00dev, E2PROM_CSR, &reg);

	eeprom.data = rt2x00dev;
	eeprom.register_read = rt61pci_eepromregister_read;
	eeprom.register_write = rt61pci_eepromregister_write;
	eeprom.width = rt2x00_get_field32(reg, E2PROM_CSR_TYPE_93C46) ?
	    PCI_EEPROM_WIDTH_93C46 : PCI_EEPROM_WIDTH_93C66;
	eeprom.reg_data_in = 0;
	eeprom.reg_data_out = 0;
	eeprom.reg_data_clock = 0;
	eeprom.reg_chip_select = 0;

	eeprom_93cx6_multiread(&eeprom, EEPROM_BASE, rt2x00dev->eeprom,
			       EEPROM_SIZE / sizeof(u16));

	/*
	 * Start validation of the data that has been read.
	 */
	mac = rt2x00_eeprom_addr(rt2x00dev, EEPROM_MAC_ADDR_0);
	if (!is_valid_ether_addr(mac)) {
		eth_random_addr(mac);
		rt2x00_eeprom_dbg(rt2x00dev, "MAC: %pM\n", mac);
	}

	rt2x00_eeprom_read(rt2x00dev, EEPROM_ANTENNA, &word);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_ANTENNA_NUM, 2);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_TX_DEFAULT,
				   ANTENNA_B);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RX_DEFAULT,
				   ANTENNA_B);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_FRAME_TYPE, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_DYN_TXAGC, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_HARDWARE_RADIO, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RF_TYPE, RF5225);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_ANTENNA, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Antenna: 0x%04x\n", word);
	}

	rt2x00_eeprom_read(rt2x00dev, EEPROM_NIC, &word);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_NIC_ENABLE_DIVERSITY, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_TX_DIVERSITY, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_RX_FIXED, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_TX_FIXED, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_EXTERNAL_LNA_BG, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CARDBUS_ACCEL, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_EXTERNAL_LNA_A, 0);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_NIC, word);
		rt2x00_eeprom_dbg(rt2x00dev, "NIC: 0x%04x\n", word);
	}

	rt2x00_eeprom_read(rt2x00dev, EEPROM_LED, &word);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_LED_LED_MODE,
				   LED_MODE_DEFAULT);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_LED, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Led: 0x%04x\n", word);
	}

	rt2x00_eeprom_read(rt2x00dev, EEPROM_FREQ, &word);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_FREQ_OFFSET, 0);
		rt2x00_set_field16(&word, EEPROM_FREQ_SEQ, 0);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_FREQ, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Freq: 0x%04x\n", word);
	}

	rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_OFFSET_BG, &word);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_BG_1, 0);
		rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_BG_2, 0);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_RSSI_OFFSET_BG, word);
		rt2x00_eeprom_dbg(rt2x00dev, "RSSI OFFSET BG: 0x%04x\n", word);
	} else {
		value = rt2x00_get_field16(word, EEPROM_RSSI_OFFSET_BG_1);
		if (value < -10 || value > 10)
			rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_BG_1, 0);
		value = rt2x00_get_field16(word, EEPROM_RSSI_OFFSET_BG_2);
		if (value < -10 || value > 10)
			rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_BG_2, 0);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_RSSI_OFFSET_BG, word);
	}

	rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_OFFSET_A, &word);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_A_1, 0);
		rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_A_2, 0);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_RSSI_OFFSET_A, word);
		rt2x00_eeprom_dbg(rt2x00dev, "RSSI OFFSET A: 0x%04x\n", word);
	} else {
		value = rt2x00_get_field16(word, EEPROM_RSSI_OFFSET_A_1);
		if (value < -10 || value > 10)
			rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_A_1, 0);
		value = rt2x00_get_field16(word, EEPROM_RSSI_OFFSET_A_2);
		if (value < -10 || value > 10)
			rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_A_2, 0);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_RSSI_OFFSET_A, word);
	}

	return 0;
}