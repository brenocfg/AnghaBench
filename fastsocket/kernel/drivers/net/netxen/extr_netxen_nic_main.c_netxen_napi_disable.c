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

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netxen_nic_disable_int (struct nx_host_sds_ring*) ; 

__attribute__((used)) static void
netxen_napi_disable(struct netxen_adapter *adapter)
{
	int ring;
	struct nx_host_sds_ring *sds_ring;
	struct netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	for (ring = 0; ring < adapter->max_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];
		netxen_nic_disable_int(sds_ring);
		napi_synchronize(&sds_ring->napi);
		napi_disable(&sds_ring->napi);
	}
}