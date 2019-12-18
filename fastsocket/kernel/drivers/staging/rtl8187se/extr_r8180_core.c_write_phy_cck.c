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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8185_write_phy (struct net_device*,int /*<<< orphan*/ ,int) ; 

void write_phy_cck (struct net_device *dev, u8 adr, u32 data)
{
	data = data & 0xff;
	rtl8185_write_phy(dev, adr, data | 0x10000);
}