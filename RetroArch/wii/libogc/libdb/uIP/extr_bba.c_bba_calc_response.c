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
typedef  int u8 ;
typedef  int u32 ;
struct uip_netif {scalar_t__ state; } ;
struct bba_priv {int revid; int devid; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_LOG (char*) ; 
 int _SHIFTR (int,int,int) ; 

__attribute__((used)) static u32 bba_calc_response(struct uip_netif *dev,u32 val)
{
	u8 revid_0, revid_eth_0, revid_eth_1;
	struct bba_priv *priv = (struct bba_priv*)dev->state;

	UIP_LOG("bba_calc_response()\n");

	revid_0 = priv->revid;
	revid_eth_0 = _SHIFTR(priv->devid,8,8);
	revid_eth_1 = priv->devid&0xff;

	u8 i0, i1, i2, i3;
	i0 = (val & 0xff000000) >> 24;
	i1 = (val & 0x00ff0000) >> 16;
	i2 = (val & 0x0000ff00) >> 8;
	i3 = (val & 0x000000ff);

	u8 c0, c1, c2, c3;
	c0 = ((i0 + i1 * 0xc1 + 0x18 + revid_0) ^ (i3 * i2 + 0x90)
	    ) & 0xff;
	c1 = ((i1 + i2 + 0x90) ^ (c0 + i0 - 0xc1)
	    ) & 0xff;
	c2 = ((i2 + 0xc8) ^ (c0 + ((revid_eth_0 + revid_0 * 0x23) ^ 0x19))
	    ) & 0xff;
	c3 = ((i0 + 0xc1) ^ (i3 + ((revid_eth_1 + 0xc8) ^ 0x90))
	    ) & 0xff;

	return ((c0 << 24) | (c1 << 16) | (c2 << 8) | c3);
}