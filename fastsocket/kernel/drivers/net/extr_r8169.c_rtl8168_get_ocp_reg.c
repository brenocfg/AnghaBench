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
typedef  int u16 ;
struct rtl8169_private {scalar_t__ mac_version; } ;

/* Variables and functions */
 scalar_t__ RTL_GIGA_MAC_VER_31 ; 

__attribute__((used)) static u16 rtl8168_get_ocp_reg(struct rtl8169_private *tp)
{
	return (tp->mac_version == RTL_GIGA_MAC_VER_31) ? 0xb8 : 0x10;
}