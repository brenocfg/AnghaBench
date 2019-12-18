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
 int rtl_ephy_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_ephy_write (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_hw_start_8105e_1 (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8105e_2(struct rtl8169_private *tp)
{
	rtl_hw_start_8105e_1(tp);
	rtl_ephy_write(tp, 0x1e, rtl_ephy_read(tp, 0x1e) | 0x8000);
}