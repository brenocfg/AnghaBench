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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ks8695_priv {int dtype; scalar_t__ phyiface_regs; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  KS8695_DTYPE_HPNA 130 
#define  KS8695_DTYPE_LAN 129 
#define  KS8695_DTYPE_WAN 128 
 scalar_t__ KS8695_WMC ; 
 int WMC_WLS ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static u32
ks8695_get_link(struct net_device *ndev)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);
	u32 ctrl;

	switch (ksp->dtype) {
	case KS8695_DTYPE_HPNA:
		/* HPNA always has link */
		return 1;
	case KS8695_DTYPE_WAN:
		/* WAN we can read the PHY for */
		ctrl = readl(ksp->phyiface_regs + KS8695_WMC);
		return ctrl & WMC_WLS;
	case KS8695_DTYPE_LAN:
		return -EOPNOTSUPP;
	}
	return 0;
}