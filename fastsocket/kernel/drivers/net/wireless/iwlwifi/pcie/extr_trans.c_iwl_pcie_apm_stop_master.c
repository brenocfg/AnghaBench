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
 int /*<<< orphan*/  CSR_RESET ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_MASTER_DISABLED ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_STOP_MASTER ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_trans*,char*) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_pcie_apm_stop_master(struct iwl_trans *trans)
{
	int ret = 0;

	/* stop device's busmaster DMA activity */
	iwl_set_bit(trans, CSR_RESET, CSR_RESET_REG_FLAG_STOP_MASTER);

	ret = iwl_poll_bit(trans, CSR_RESET,
			   CSR_RESET_REG_FLAG_MASTER_DISABLED,
			   CSR_RESET_REG_FLAG_MASTER_DISABLED, 100);
	if (ret)
		IWL_WARN(trans, "Master Disable Timed Out, 100 usec\n");

	IWL_DEBUG_INFO(trans, "stop master\n");

	return ret;
}