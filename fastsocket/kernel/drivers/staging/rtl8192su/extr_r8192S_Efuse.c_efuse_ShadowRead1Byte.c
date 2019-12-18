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
typedef  size_t u16 ;
struct r8192_priv {int /*<<< orphan*/ ** EfuseMap; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t EFUSE_MODIFY_MAP ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static	void
efuse_ShadowRead1Byte(struct net_device*	dev,	u16 Offset,	u8 *Value)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	*Value = priv->EfuseMap[EFUSE_MODIFY_MAP][Offset];

}