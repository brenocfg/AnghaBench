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
typedef  scalar_t__ u16 ;
struct rtl8169_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_warn (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl_apply_firmware (struct rtl8169_private*) ; 
 scalar_t__ rtl_readphy (struct rtl8169_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_apply_firmware_cond(struct rtl8169_private *tp, u8 reg, u16 val)
{
	if (rtl_readphy(tp, reg) != val)
		netif_warn(tp, hw, tp->dev, "chipset not ready for firmware\n");
	else
		rtl_apply_firmware(tp);
}