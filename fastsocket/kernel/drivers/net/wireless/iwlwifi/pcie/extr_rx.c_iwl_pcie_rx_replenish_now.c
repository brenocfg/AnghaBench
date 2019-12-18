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
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  iwl_pcie_rxq_alloc_rbs (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_rxq_restock (struct iwl_trans*) ; 

__attribute__((used)) static void iwl_pcie_rx_replenish_now(struct iwl_trans *trans)
{
	iwl_pcie_rxq_alloc_rbs(trans, GFP_ATOMIC);

	iwl_pcie_rxq_restock(trans);
}