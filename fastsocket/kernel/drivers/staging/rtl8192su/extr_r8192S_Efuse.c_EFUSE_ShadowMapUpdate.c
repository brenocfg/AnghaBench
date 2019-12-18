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
struct r8192_priv {int AutoloadFailFlag; int /*<<< orphan*/ ** EfuseMap; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t EFUSE_INIT_MAP ; 
 size_t EFUSE_MODIFY_MAP ; 
 int /*<<< orphan*/  HWSET_MAX_SIZE_92S ; 
 int /*<<< orphan*/  efuse_ReadAllMap (struct net_device*,int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

extern void EFUSE_ShadowMapUpdate(struct net_device* dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	if (priv->AutoloadFailFlag == true){
		memset(&(priv->EfuseMap[EFUSE_INIT_MAP][0]), 0xff, 128);
	}else{
		efuse_ReadAllMap(dev, &priv->EfuseMap[EFUSE_INIT_MAP][0]);
	}
	//PlatformMoveMemory(&priv->EfuseMap[EFUSE_MODIFY_MAP][0],
		//&priv->EfuseMap[EFUSE_INIT_MAP][0], HWSET_MAX_SIZE_92S);//FIXLZM
	memcpy(&priv->EfuseMap[EFUSE_MODIFY_MAP][0],
		&priv->EfuseMap[EFUSE_INIT_MAP][0], HWSET_MAX_SIZE_92S);

}