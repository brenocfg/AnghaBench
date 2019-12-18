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
struct rtl8169_private {int dummy; } ;
struct phy_reg {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct phy_reg const*) ; 
 int /*<<< orphan*/  ERIAR_EXGMAC ; 
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 int /*<<< orphan*/  rtl_apply_firmware (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_w1w0_eri (struct rtl8169_private*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_w1w0_phy (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_writephy_batch (struct rtl8169_private*,struct phy_reg const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8168e_2_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		/* Enable Delay cap */
		{ 0x1f, 0x0004 },
		{ 0x1f, 0x0007 },
		{ 0x1e, 0x00ac },
		{ 0x18, 0x0006 },
		{ 0x1f, 0x0002 },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0000 },

		/* Channel estimation fine tune */
		{ 0x1f, 0x0003 },
		{ 0x09, 0xa20f },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0000 },

		/* Green Setting */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b5b },
		{ 0x06, 0x9222 },
		{ 0x05, 0x8b6d },
		{ 0x06, 0x8000 },
		{ 0x05, 0x8b76 },
		{ 0x06, 0x8000 },
		{ 0x1f, 0x0000 }
	};

	rtl_apply_firmware(tp);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	/* For 4-corner performance improve */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b80);
	rtl_w1w0_phy(tp, 0x17, 0x0006, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* PHY auto speed down */
	rtl_writephy(tp, 0x1f, 0x0004);
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x002d);
	rtl_w1w0_phy(tp, 0x18, 0x0010, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_w1w0_phy(tp, 0x14, 0x8000, 0x0000);

	/* improve 10M EEE waveform */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b86);
	rtl_w1w0_phy(tp, 0x06, 0x0001, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* Improve 2-pair detection performance */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x4000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* EEE setting */
	rtl_w1w0_eri(tp, 0x1b0, ERIAR_MASK_1111, 0x0000, 0x0003, ERIAR_EXGMAC);
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x2000);
	rtl_writephy(tp, 0x1f, 0x0004);
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x0020);
	rtl_w1w0_phy(tp, 0x15, 0x0000, 0x0100);
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, 0x0d, 0x0007);
	rtl_writephy(tp, 0x0e, 0x003c);
	rtl_writephy(tp, 0x0d, 0x4007);
	rtl_writephy(tp, 0x0e, 0x0000);
	rtl_writephy(tp, 0x0d, 0x0000);

	/* Green feature */
	rtl_writephy(tp, 0x1f, 0x0003);
	rtl_w1w0_phy(tp, 0x19, 0x0000, 0x0001);
	rtl_w1w0_phy(tp, 0x10, 0x0000, 0x0400);
	rtl_writephy(tp, 0x1f, 0x0000);
}