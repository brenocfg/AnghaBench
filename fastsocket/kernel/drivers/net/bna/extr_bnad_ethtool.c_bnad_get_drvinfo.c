#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_5__ {TYPE_1__ ioceth; } ;
struct bnad {int /*<<< orphan*/  pcidev; int /*<<< orphan*/  bna_lock; TYPE_2__ bna; } ;
struct TYPE_6__ {int /*<<< orphan*/  fw_ver; } ;
struct bfa_ioc_attr {TYPE_3__ adapter_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_NAME ; 
 int /*<<< orphan*/  BNAD_VERSION ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bfa_nw_ioc_get_attr (int /*<<< orphan*/ *,struct bfa_ioc_attr*) ; 
 int /*<<< orphan*/  kfree (struct bfa_ioc_attr*) ; 
 struct bfa_ioc_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bnad_get_drvinfo(struct net_device *netdev, struct ethtool_drvinfo *drvinfo)
{
	struct bnad *bnad = netdev_priv(netdev);
	struct bfa_ioc_attr *ioc_attr;
	unsigned long flags;

	strlcpy(drvinfo->driver, BNAD_NAME, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, BNAD_VERSION, sizeof(drvinfo->version));

	ioc_attr = kzalloc(sizeof(*ioc_attr), GFP_KERNEL);
	if (ioc_attr) {
		spin_lock_irqsave(&bnad->bna_lock, flags);
		bfa_nw_ioc_get_attr(&bnad->bna.ioceth.ioc, ioc_attr);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);

		strlcpy(drvinfo->fw_version, ioc_attr->adapter_attr.fw_ver,
			sizeof(drvinfo->fw_version));
		kfree(ioc_attr);
	}

	strlcpy(drvinfo->bus_info, pci_name(bnad->pcidev),
		sizeof(drvinfo->bus_info));
}