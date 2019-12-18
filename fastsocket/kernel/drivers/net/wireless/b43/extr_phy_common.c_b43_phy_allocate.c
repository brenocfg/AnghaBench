#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct b43_phy {int type; TYPE_1__* ops; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct TYPE_7__ {int (* allocate ) (struct b43_wldev*) ;} ;

/* Variables and functions */
#define  B43_PHYTYPE_A 133 
#define  B43_PHYTYPE_G 132 
#define  B43_PHYTYPE_HT 131 
#define  B43_PHYTYPE_LCN 130 
#define  B43_PHYTYPE_LP 129 
#define  B43_PHYTYPE_N 128 
 scalar_t__ B43_WARN_ON (int) ; 
 int ENODEV ; 
 TYPE_1__ b43_phyops_a ; 
 TYPE_1__ b43_phyops_g ; 
 TYPE_1__ b43_phyops_ht ; 
 TYPE_1__ b43_phyops_lcn ; 
 TYPE_1__ b43_phyops_lp ; 
 TYPE_1__ b43_phyops_n ; 
 int stub1 (struct b43_wldev*) ; 

int b43_phy_allocate(struct b43_wldev *dev)
{
	struct b43_phy *phy = &(dev->phy);
	int err;

	phy->ops = NULL;

	switch (phy->type) {
	case B43_PHYTYPE_A:
		phy->ops = &b43_phyops_a;
		break;
	case B43_PHYTYPE_G:
		phy->ops = &b43_phyops_g;
		break;
	case B43_PHYTYPE_N:
#ifdef CONFIG_B43_PHY_N
		phy->ops = &b43_phyops_n;
#endif
		break;
	case B43_PHYTYPE_LP:
#ifdef CONFIG_B43_PHY_LP
		phy->ops = &b43_phyops_lp;
#endif
		break;
	case B43_PHYTYPE_HT:
#ifdef CONFIG_B43_PHY_HT
		phy->ops = &b43_phyops_ht;
#endif
		break;
	case B43_PHYTYPE_LCN:
#ifdef CONFIG_B43_PHY_LCN
		phy->ops = &b43_phyops_lcn;
#endif
		break;
	}
	if (B43_WARN_ON(!phy->ops))
		return -ENODEV;

	err = phy->ops->allocate(dev);
	if (err)
		phy->ops = NULL;

	return err;
}