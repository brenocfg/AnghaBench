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
struct nx_host_tx_ring {int /*<<< orphan*/  sw_consumer; int /*<<< orphan*/  crb_cmd_consumer; } ;
struct netxen_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NXWRIO (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
netxen_nic_update_cmd_consumer(struct netxen_adapter *adapter,
		struct nx_host_tx_ring *tx_ring)
{
	NXWRIO(adapter, tx_ring->crb_cmd_consumer, tx_ring->sw_consumer);
}