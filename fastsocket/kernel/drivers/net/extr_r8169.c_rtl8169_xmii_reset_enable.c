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

/* Variables and functions */
 unsigned int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 unsigned int rtl_readphy (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void rtl8169_xmii_reset_enable(struct rtl8169_private *tp)
{
	unsigned int val;

	val = rtl_readphy(tp, MII_BMCR) | BMCR_RESET;
	rtl_writephy(tp, MII_BMCR, val & 0xffff);
}