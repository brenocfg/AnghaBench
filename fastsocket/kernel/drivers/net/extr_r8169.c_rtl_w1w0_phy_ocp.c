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
 int r8168_phy_ocp_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  r8168_phy_ocp_write (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl_w1w0_phy_ocp(struct rtl8169_private *tp, int reg, int p, int m)
{
	int val;

	val = r8168_phy_ocp_read(tp, reg);
	r8168_phy_ocp_write(tp, reg, (val | p) & ~m);
}