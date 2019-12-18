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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int,int const) ; 
 int r8168_phy_ocp_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  r8168_phy_ocp_write (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_apply_firmware (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_w1w0_phy_ocp (struct rtl8169_private*,int,int,int) ; 

__attribute__((used)) static void rtl8168g_1_hw_phy_config(struct rtl8169_private *tp)
{
	static const u16 mac_ocp_patch[] = {
		0xe008, 0xe01b, 0xe01d, 0xe01f,
		0xe021, 0xe023, 0xe025, 0xe027,
		0x49d2, 0xf10d, 0x766c, 0x49e2,
		0xf00a, 0x1ec0, 0x8ee1, 0xc60a,

		0x77c0, 0x4870, 0x9fc0, 0x1ea0,
		0xc707, 0x8ee1, 0x9d6c, 0xc603,
		0xbe00, 0xb416, 0x0076, 0xe86c,
		0xc602, 0xbe00, 0x0000, 0xc602,

		0xbe00, 0x0000, 0xc602, 0xbe00,
		0x0000, 0xc602, 0xbe00, 0x0000,
		0xc602, 0xbe00, 0x0000, 0xc602,
		0xbe00, 0x0000, 0xc602, 0xbe00,

		0x0000, 0x0000, 0x0000, 0x0000
	};
	u32 i;

	/* Patch code for GPHY reset */
	for (i = 0; i < ARRAY_SIZE(mac_ocp_patch); i++)
		r8168_mac_ocp_write(tp, 0xf800 + 2*i, mac_ocp_patch[i]);
	r8168_mac_ocp_write(tp, 0xfc26, 0x8000);
	r8168_mac_ocp_write(tp, 0xfc28, 0x0075);

	rtl_apply_firmware(tp);

	if (r8168_phy_ocp_read(tp, 0xa460) & 0x0100)
		rtl_w1w0_phy_ocp(tp, 0xbcc4, 0x0000, 0x8000);
	else
		rtl_w1w0_phy_ocp(tp, 0xbcc4, 0x8000, 0x0000);

	if (r8168_phy_ocp_read(tp, 0xa466) & 0x0100)
		rtl_w1w0_phy_ocp(tp, 0xc41a, 0x0002, 0x0000);
	else
		rtl_w1w0_phy_ocp(tp, 0xbcc4, 0x0000, 0x0002);

	rtl_w1w0_phy_ocp(tp, 0xa442, 0x000c, 0x0000);
	rtl_w1w0_phy_ocp(tp, 0xa4b2, 0x0004, 0x0000);

	r8168_phy_ocp_write(tp, 0xa436, 0x8012);
	rtl_w1w0_phy_ocp(tp, 0xa438, 0x8000, 0x0000);

	rtl_w1w0_phy_ocp(tp, 0xc422, 0x4000, 0x2000);
}