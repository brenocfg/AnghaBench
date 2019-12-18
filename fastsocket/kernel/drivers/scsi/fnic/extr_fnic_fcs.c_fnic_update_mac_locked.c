#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * ctl_src_addr; } ;
struct fnic {int /*<<< orphan*/  vdev; TYPE_2__* lport; int /*<<< orphan*/ * data_src_addr; TYPE_1__ ctlr; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FNIC_FCS_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ compare_ether_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_add_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_dev_del_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fnic_update_mac_locked(struct fnic *fnic, u8 *new)
{
	u8 *ctl = fnic->ctlr.ctl_src_addr;
	u8 *data = fnic->data_src_addr;

	if (is_zero_ether_addr(new))
		new = ctl;
	if (!compare_ether_addr(data, new))
		return;
	FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host, "update_mac %pM\n", new);
	if (!is_zero_ether_addr(data) && compare_ether_addr(data, ctl))
		vnic_dev_del_addr(fnic->vdev, data);
	memcpy(data, new, ETH_ALEN);
	if (compare_ether_addr(new, ctl))
		vnic_dev_add_addr(fnic->vdev, new);
}