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
struct nes_vnic_mgt {int /*<<< orphan*/  rx_skbs_needed; int /*<<< orphan*/  rx_skb_timer_running; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_replenish_mgt_rq (struct nes_vnic_mgt*) ; 

__attribute__((used)) static void nes_mgt_rq_wqes_timeout(unsigned long parm)
{
	struct nes_vnic_mgt *mgtvnic = (struct nes_vnic_mgt *)parm;

	atomic_set(&mgtvnic->rx_skb_timer_running, 0);
	if (atomic_read(&mgtvnic->rx_skbs_needed))
		nes_replenish_mgt_rq(mgtvnic);
}