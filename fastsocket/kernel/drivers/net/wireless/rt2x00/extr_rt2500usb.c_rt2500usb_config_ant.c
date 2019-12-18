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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int dummy; } ;
struct antenna_setup {int rx; int tx; } ;

/* Variables and functions */
#define  ANTENNA_A 130 
#define  ANTENNA_B 129 
#define  ANTENNA_HW_DIVERSITY 128 
 int ANTENNA_SW_DIVERSITY ; 
 int /*<<< orphan*/  BBP_R14_RX_ANTENNA ; 
 int /*<<< orphan*/  BBP_R14_RX_IQ_FLIP ; 
 int /*<<< orphan*/  BBP_R2_TX_ANTENNA ; 
 int /*<<< orphan*/  BBP_R2_TX_IQ_FLIP ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PHY_CSR5 ; 
 int /*<<< orphan*/  PHY_CSR5_CCK ; 
 int /*<<< orphan*/  PHY_CSR5_CCK_FLIP ; 
 int /*<<< orphan*/  PHY_CSR6 ; 
 int /*<<< orphan*/  PHY_CSR6_OFDM ; 
 int /*<<< orphan*/  PHY_CSR6_OFDM_FLIP ; 
 int /*<<< orphan*/  RF2525E ; 
 int /*<<< orphan*/  RF5222 ; 
 int /*<<< orphan*/  rt2500usb_bbp_read (struct rt2x00_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2500usb_bbp_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rf (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2500usb_config_ant(struct rt2x00_dev *rt2x00dev,
				 struct antenna_setup *ant)
{
	u8 r2;
	u8 r14;
	u16 csr5;
	u16 csr6;

	/*
	 * We should never come here because rt2x00lib is supposed
	 * to catch this and send us the correct antenna explicitely.
	 */
	BUG_ON(ant->rx == ANTENNA_SW_DIVERSITY ||
	       ant->tx == ANTENNA_SW_DIVERSITY);

	rt2500usb_bbp_read(rt2x00dev, 2, &r2);
	rt2500usb_bbp_read(rt2x00dev, 14, &r14);
	rt2500usb_register_read(rt2x00dev, PHY_CSR5, &csr5);
	rt2500usb_register_read(rt2x00dev, PHY_CSR6, &csr6);

	/*
	 * Configure the TX antenna.
	 */
	switch (ant->tx) {
	case ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r2, BBP_R2_TX_ANTENNA, 1);
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK, 1);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM, 1);
		break;
	case ANTENNA_A:
		rt2x00_set_field8(&r2, BBP_R2_TX_ANTENNA, 0);
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK, 0);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM, 0);
		break;
	case ANTENNA_B:
	default:
		rt2x00_set_field8(&r2, BBP_R2_TX_ANTENNA, 2);
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK, 2);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM, 2);
		break;
	}

	/*
	 * Configure the RX antenna.
	 */
	switch (ant->rx) {
	case ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r14, BBP_R14_RX_ANTENNA, 1);
		break;
	case ANTENNA_A:
		rt2x00_set_field8(&r14, BBP_R14_RX_ANTENNA, 0);
		break;
	case ANTENNA_B:
	default:
		rt2x00_set_field8(&r14, BBP_R14_RX_ANTENNA, 2);
		break;
	}

	/*
	 * RT2525E and RT5222 need to flip TX I/Q
	 */
	if (rt2x00_rf(rt2x00dev, RF2525E) || rt2x00_rf(rt2x00dev, RF5222)) {
		rt2x00_set_field8(&r2, BBP_R2_TX_IQ_FLIP, 1);
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK_FLIP, 1);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM_FLIP, 1);

		/*
		 * RT2525E does not need RX I/Q Flip.
		 */
		if (rt2x00_rf(rt2x00dev, RF2525E))
			rt2x00_set_field8(&r14, BBP_R14_RX_IQ_FLIP, 0);
	} else {
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK_FLIP, 0);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM_FLIP, 0);
	}

	rt2500usb_bbp_write(rt2x00dev, 2, r2);
	rt2500usb_bbp_write(rt2x00dev, 14, r14);
	rt2500usb_register_write(rt2x00dev, PHY_CSR5, csr5);
	rt2500usb_register_write(rt2x00dev, PHY_CSR6, csr6);
}