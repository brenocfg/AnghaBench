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
struct nx_host_sds_ring {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct netxen_recv_context {struct nx_host_sds_ring* sds_rings; } ;
struct netxen_adapter {int flags; int max_sds_rings; int /*<<< orphan*/  irq; struct netxen_recv_context recv_ctx; struct net_device* netdev; } ;
struct net_device {char* name; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 unsigned long IRQF_SAMPLE_RANDOM ; 
 unsigned long IRQF_SHARED ; 
 int NETXEN_NIC_MSIX_ENABLED ; 
 int NETXEN_NIC_MSI_ENABLED ; 
 int /*<<< orphan*/  netxen_intr ; 
 int /*<<< orphan*/  netxen_msi_intr ; 
 int /*<<< orphan*/  netxen_msix_intr ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct nx_host_sds_ring*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int
netxen_nic_request_irq(struct netxen_adapter *adapter)
{
	irq_handler_t handler;
	struct nx_host_sds_ring *sds_ring;
	int err, ring;

	unsigned long flags = IRQF_SAMPLE_RANDOM;
	struct net_device *netdev = adapter->netdev;
	struct netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	if (adapter->flags & NETXEN_NIC_MSIX_ENABLED)
		handler = netxen_msix_intr;
	else if (adapter->flags & NETXEN_NIC_MSI_ENABLED)
		handler = netxen_msi_intr;
	else {
		flags |= IRQF_SHARED;
		handler = netxen_intr;
	}
	adapter->irq = netdev->irq;

	for (ring = 0; ring < adapter->max_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];
		sprintf(sds_ring->name, "%s[%d]", netdev->name, ring);
		err = request_irq(sds_ring->irq, handler,
				  flags, sds_ring->name, sds_ring);
		if (err)
			return err;
	}

	return 0;
}