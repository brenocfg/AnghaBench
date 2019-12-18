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
struct ephy_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ephy_info const*) ; 
 int /*<<< orphan*/  __rtl_hw_start_8168cp (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_csi_access_enable_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_hw_start_8168cp_1(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168cp[] = {
		{ 0x01, 0,	0x0001 },
		{ 0x02, 0x0800,	0x1000 },
		{ 0x03, 0,	0x0042 },
		{ 0x06, 0x0080,	0x0000 },
		{ 0x07, 0,	0x2000 }
	};

	rtl_csi_access_enable_2(tp);

	rtl_ephy_init(tp, e_info_8168cp, ARRAY_SIZE(e_info_8168cp));

	__rtl_hw_start_8168cp(tp);
}