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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_pcie_reset_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_tx_start (struct iwl_trans*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_trans_pcie_fw_alive(struct iwl_trans *trans, u32 scd_addr)
{
	iwl_pcie_reset_ict(trans);
	iwl_pcie_tx_start(trans, scd_addr);
}