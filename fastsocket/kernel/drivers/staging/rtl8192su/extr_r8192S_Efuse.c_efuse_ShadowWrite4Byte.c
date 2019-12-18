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
typedef  void* u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct r8192_priv {void*** EfuseMap; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t EFUSE_MODIFY_MAP ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static	void
efuse_ShadowWrite4Byte(struct net_device*	dev,	u16 Offset,	u32 Value)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	priv->EfuseMap[EFUSE_MODIFY_MAP][Offset] = (u8)(Value&0x000000FF);
	priv->EfuseMap[EFUSE_MODIFY_MAP][Offset+1] = (u8)((Value>>8)&0x0000FF);
	priv->EfuseMap[EFUSE_MODIFY_MAP][Offset+2] = (u8)((Value>>16)&0x00FF);
	priv->EfuseMap[EFUSE_MODIFY_MAP][Offset+3] = (u8)((Value>>24)&0xFF);

}