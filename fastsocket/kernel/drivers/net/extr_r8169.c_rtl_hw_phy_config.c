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
struct rtl8169_private {int mac_version; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  RTL_GIGA_MAC_VER_01 163 
#define  RTL_GIGA_MAC_VER_02 162 
#define  RTL_GIGA_MAC_VER_03 161 
#define  RTL_GIGA_MAC_VER_04 160 
#define  RTL_GIGA_MAC_VER_05 159 
#define  RTL_GIGA_MAC_VER_06 158 
#define  RTL_GIGA_MAC_VER_07 157 
#define  RTL_GIGA_MAC_VER_08 156 
#define  RTL_GIGA_MAC_VER_09 155 
#define  RTL_GIGA_MAC_VER_11 154 
#define  RTL_GIGA_MAC_VER_12 153 
#define  RTL_GIGA_MAC_VER_17 152 
#define  RTL_GIGA_MAC_VER_18 151 
#define  RTL_GIGA_MAC_VER_19 150 
#define  RTL_GIGA_MAC_VER_20 149 
#define  RTL_GIGA_MAC_VER_21 148 
#define  RTL_GIGA_MAC_VER_22 147 
#define  RTL_GIGA_MAC_VER_23 146 
#define  RTL_GIGA_MAC_VER_24 145 
#define  RTL_GIGA_MAC_VER_25 144 
#define  RTL_GIGA_MAC_VER_26 143 
#define  RTL_GIGA_MAC_VER_27 142 
#define  RTL_GIGA_MAC_VER_28 141 
#define  RTL_GIGA_MAC_VER_29 140 
#define  RTL_GIGA_MAC_VER_30 139 
#define  RTL_GIGA_MAC_VER_31 138 
#define  RTL_GIGA_MAC_VER_32 137 
#define  RTL_GIGA_MAC_VER_33 136 
#define  RTL_GIGA_MAC_VER_34 135 
#define  RTL_GIGA_MAC_VER_35 134 
#define  RTL_GIGA_MAC_VER_36 133 
#define  RTL_GIGA_MAC_VER_37 132 
#define  RTL_GIGA_MAC_VER_38 131 
#define  RTL_GIGA_MAC_VER_39 130 
#define  RTL_GIGA_MAC_VER_40 129 
#define  RTL_GIGA_MAC_VER_41 128 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8102e_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8105e_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8106e_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168bb_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168bef_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168c_1_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168c_2_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168c_3_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168c_4_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168cp_1_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168cp_2_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168d_1_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168d_2_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168d_3_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168d_4_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168e_1_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168e_2_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168f_1_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168f_2_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_1_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_print_mac_version (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169s_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169sb_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169scd_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169sce_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8402_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8411_hw_phy_config (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_phy_config(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl8169_print_mac_version(tp);

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_01:
		break;
	case RTL_GIGA_MAC_VER_02:
	case RTL_GIGA_MAC_VER_03:
		rtl8169s_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_04:
		rtl8169sb_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_05:
		rtl8169scd_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_06:
		rtl8169sce_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_07:
	case RTL_GIGA_MAC_VER_08:
	case RTL_GIGA_MAC_VER_09:
		rtl8102e_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_11:
		rtl8168bb_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_12:
		rtl8168bef_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_17:
		rtl8168bef_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_18:
		rtl8168cp_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_19:
		rtl8168c_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_20:
		rtl8168c_2_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_21:
		rtl8168c_3_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_22:
		rtl8168c_4_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_23:
	case RTL_GIGA_MAC_VER_24:
		rtl8168cp_2_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_25:
		rtl8168d_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_26:
		rtl8168d_2_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_27:
		rtl8168d_3_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_28:
		rtl8168d_4_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_29:
	case RTL_GIGA_MAC_VER_30:
		rtl8105e_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_31:
		/* None. */
		break;
	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
		rtl8168e_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_34:
		rtl8168e_2_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_35:
		rtl8168f_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_36:
		rtl8168f_2_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_37:
		rtl8402_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_38:
		rtl8411_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_39:
		rtl8106e_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_40:
		rtl8168g_1_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_41:
	default:
		break;
	}
}