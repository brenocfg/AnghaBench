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
struct net_device {int dummy; } ;
struct enic {unsigned int rq_count; int /*<<< orphan*/ * napi; int /*<<< orphan*/  vdev; struct net_device* netdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int enic_alloc_vnic_resources (struct enic*) ; 
 int /*<<< orphan*/  enic_clear_intr_mode (struct enic*) ; 
 int enic_dev_intr_coal_timer_info (struct enic*) ; 
 int /*<<< orphan*/  enic_free_vnic_resources (struct enic*) ; 
 struct device* enic_get_dev (struct enic*) ; 
 int /*<<< orphan*/  enic_get_res_counts (struct enic*) ; 
 int enic_get_vnic_config (struct enic*) ; 
 int /*<<< orphan*/  enic_init_vnic_resources (struct enic*) ; 
 int /*<<< orphan*/  enic_poll ; 
 int /*<<< orphan*/  enic_poll_msix ; 
 int enic_set_intr_mode (struct enic*) ; 
 int enic_set_rss_nic_cfg (struct enic*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_intr_coal_timer_info_default (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_dev_init(struct enic *enic)
{
	struct device *dev = enic_get_dev(enic);
	struct net_device *netdev = enic->netdev;
	unsigned int i;
	int err;

	/* Get interrupt coalesce timer info */
	err = enic_dev_intr_coal_timer_info(enic);
	if (err) {
		dev_warn(dev, "Using default conversion factor for "
			"interrupt coalesce timer\n");
		vnic_dev_intr_coal_timer_info_default(enic->vdev);
	}

	/* Get vNIC configuration
	 */

	err = enic_get_vnic_config(enic);
	if (err) {
		dev_err(dev, "Get vNIC configuration failed, aborting\n");
		return err;
	}

	/* Get available resource counts
	 */

	enic_get_res_counts(enic);

	/* Set interrupt mode based on resource counts and system
	 * capabilities
	 */

	err = enic_set_intr_mode(enic);
	if (err) {
		dev_err(dev, "Failed to set intr mode based on resource "
			"counts and system capabilities, aborting\n");
		return err;
	}

	/* Allocate and configure vNIC resources
	 */

	err = enic_alloc_vnic_resources(enic);
	if (err) {
		dev_err(dev, "Failed to alloc vNIC resources, aborting\n");
		goto err_out_free_vnic_resources;
	}

	enic_init_vnic_resources(enic);

	err = enic_set_rss_nic_cfg(enic);
	if (err) {
		dev_err(dev, "Failed to config nic, aborting\n");
		goto err_out_free_vnic_resources;
	}

	switch (vnic_dev_get_intr_mode(enic->vdev)) {
	default:
		netif_napi_add(netdev, &enic->napi[0], enic_poll, 64);
		break;
	case VNIC_DEV_INTR_MODE_MSIX:
		for (i = 0; i < enic->rq_count; i++)
			netif_napi_add(netdev, &enic->napi[i],
				enic_poll_msix, 64);
		break;
	}

	return 0;

err_out_free_vnic_resources:
	enic_clear_intr_mode(enic);
	enic_free_vnic_resources(enic);

	return err;
}