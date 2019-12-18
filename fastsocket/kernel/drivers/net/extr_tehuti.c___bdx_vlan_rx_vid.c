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
typedef  int uint16_t ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct bdx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG2 (char*,int,...) ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int READ_REG (struct bdx_priv*,int) ; 
 int /*<<< orphan*/  RET () ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int,int) ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 
 int regVLAN_0 ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __bdx_vlan_rx_vid(struct net_device *ndev, uint16_t vid, int enable)
{
	struct bdx_priv *priv = netdev_priv(ndev);
	u32 reg, bit, val;

	ENTER;
	DBG2("vid=%d value=%d\n", (int)vid, enable);
	if (unlikely(vid >= 4096)) {
		ERR("tehuti: invalid VID: %u (> 4096)\n", vid);
		RET();
	}
	reg = regVLAN_0 + (vid / 32) * 4;
	bit = 1 << vid % 32;
	val = READ_REG(priv, reg);
	DBG2("reg=%x, val=%x, bit=%d\n", reg, val, bit);
	if (enable)
		val |= bit;
	else
		val &= ~bit;
	DBG2("new val %x\n", val);
	WRITE_REG(priv, reg, val);
	RET();
}