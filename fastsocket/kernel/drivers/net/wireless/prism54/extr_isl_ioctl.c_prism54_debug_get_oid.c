#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; } ;
struct islpci_mgmtframe {int /*<<< orphan*/  data; TYPE_1__* header; } ;
struct TYPE_6__ {int priv_oid; int /*<<< orphan*/  ndev; } ;
typedef  TYPE_2__ islpci_private ;
struct TYPE_5__ {scalar_t__ operation; int length; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PIMFOR_OP_ERROR ; 
 int /*<<< orphan*/  PIMFOR_OP_GET ; 
 scalar_t__ PRV_STATE_INIT ; 
 scalar_t__ islpci_get_state (TYPE_2__*) ; 
 int /*<<< orphan*/  islpci_mgt_release (struct islpci_mgmtframe*) ; 
 int islpci_mgt_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,struct islpci_mgmtframe**) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
prism54_debug_get_oid(struct net_device *ndev, struct iw_request_info *info,
		      struct iw_point *data, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct islpci_mgmtframe *response;
	int ret = -EIO;

	printk("%s: get_oid 0x%08X\n", ndev->name, priv->priv_oid);
	data->length = 0;

	if (islpci_get_state(priv) >= PRV_STATE_INIT) {
		ret =
		    islpci_mgt_transaction(priv->ndev, PIMFOR_OP_GET,
					   priv->priv_oid, extra, 256,
					   &response);
		printk("%s: ret: %i\n", ndev->name, ret);
		if (ret || !response
		    || response->header->operation == PIMFOR_OP_ERROR) {
			if (response) {
				islpci_mgt_release(response);
			}
			printk("%s: EIO\n", ndev->name);
			ret = -EIO;
		}
		if (!ret) {
			data->length = response->header->length;
			memcpy(extra, response->data, data->length);
			islpci_mgt_release(response);
			printk("%s: len: %i\n", ndev->name, data->length);
		}
	}

	return ret;
}