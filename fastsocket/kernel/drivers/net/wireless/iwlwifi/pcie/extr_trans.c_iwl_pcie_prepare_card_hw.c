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
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_PREPARE ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 int iwl_pcie_set_hw_ready (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iwl_pcie_prepare_card_hw(struct iwl_trans *trans)
{
	int ret;
	int t = 0;

	IWL_DEBUG_INFO(trans, "iwl_trans_prepare_card_hw enter\n");

	ret = iwl_pcie_set_hw_ready(trans);
	/* If the card is ready, exit 0 */
	if (ret >= 0)
		return 0;

	/* If HW is not ready, prepare the conditions to check again */
	iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_PREPARE);

	do {
		ret = iwl_pcie_set_hw_ready(trans);
		if (ret >= 0)
			return 0;

		usleep_range(200, 1000);
		t += 200;
	} while (t < 150000);

	return ret;
}