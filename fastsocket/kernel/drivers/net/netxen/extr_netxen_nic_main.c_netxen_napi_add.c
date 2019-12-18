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
struct nx_host_sds_ring {int /*<<< orphan*/  napi; } ;
struct netxen_recv_context {struct nx_host_sds_ring* sds_rings; } ;
struct netxen_adapter {int max_sds_rings; struct netxen_recv_context recv_ctx; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NETXEN_NETDEV_WEIGHT ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netxen_alloc_sds_rings (struct netxen_recv_context*,int) ; 
 int /*<<< orphan*/  netxen_nic_poll ; 

__attribute__((used)) static int
netxen_napi_add(struct netxen_adapter *adapter, struct net_device *netdev)
{
	int ring;
	struct nx_host_sds_ring *sds_ring;
	struct netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	if (netxen_alloc_sds_rings(recv_ctx, adapter->max_sds_rings))
		return -ENOMEM;

	for (ring = 0; ring < adapter->max_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];
		netif_napi_add(netdev, &sds_ring->napi,
				netxen_nic_poll, NETXEN_NETDEV_WEIGHT);
	}

	return 0;
}