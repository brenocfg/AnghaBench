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
struct netvsc_device_info {int /*<<< orphan*/  ring_size; } ;
struct netvsc_device {scalar_t__ nvsp_version; int start_remove; scalar_t__ destroy; } ;
struct net_device_context {struct hv_device* device_ctx; int /*<<< orphan*/  work; int /*<<< orphan*/  dwork; } ;
struct net_device {int mtu; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ETH_DATA_LEN ; 
 int NETVSC_MTU ; 
 scalar_t__ NVSP_PROTOCOL_VERSION_2 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct netvsc_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,struct net_device*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  ring_size ; 
 int /*<<< orphan*/  rndis_filter_device_add (struct hv_device*,struct netvsc_device_info*) ; 
 int /*<<< orphan*/  rndis_filter_device_remove (struct hv_device*) ; 

__attribute__((used)) static int netvsc_change_mtu(struct net_device *ndev, int mtu)
{
	struct net_device_context *ndevctx = netdev_priv(ndev);
	struct hv_device *hdev =  ndevctx->device_ctx;
	struct netvsc_device *nvdev = hv_get_drvdata(hdev);
	struct netvsc_device_info device_info;
	int limit = ETH_DATA_LEN;

	if (nvdev == NULL || nvdev->destroy)
		return -ENODEV;

	if (nvdev->nvsp_version == NVSP_PROTOCOL_VERSION_2)
		limit = NETVSC_MTU;

	if (mtu < 68 || mtu > limit)
		return -EINVAL;

	nvdev->start_remove = true;
	cancel_delayed_work_sync(&ndevctx->dwork);
	cancel_work_sync(&ndevctx->work);
	netif_tx_disable(ndev);
	rndis_filter_device_remove(hdev);

	ndev->mtu = mtu;

	ndevctx->device_ctx = hdev;
	hv_set_drvdata(hdev, ndev);
	device_info.ring_size = ring_size;
	rndis_filter_device_add(hdev, &device_info);
	netif_wake_queue(ndev);

	return 0;
}