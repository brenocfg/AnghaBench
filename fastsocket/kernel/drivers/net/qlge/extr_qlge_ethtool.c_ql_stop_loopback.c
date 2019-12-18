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
struct ql_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; int /*<<< orphan*/  link_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LOOPBACK_PCS ; 
 int /*<<< orphan*/  QL_LB_LINK_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_mb_set_port_cfg (struct ql_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_stop_loopback(struct ql_adapter *qdev)
{
	qdev->link_config &= ~CFG_LOOPBACK_PCS;
	ql_mb_set_port_cfg(qdev);
	if (test_bit(QL_LB_LINK_UP, &qdev->flags)) {
		netif_carrier_on(qdev->ndev);
		clear_bit(QL_LB_LINK_UP, &qdev->flags);
	}
}