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
struct iwl_trans_pcie {unsigned long long ict_tbl; int ict_tbl_dma; int /*<<< orphan*/  inta_mask; scalar_t__ ict_index; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT_BIT_RX_PERIODIC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICT_SIZE ; 
 int /*<<< orphan*/  IWL_DEBUG_ISR (struct iwl_trans*,char*,unsigned long long) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned long long dma_alloc_coherent (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_free_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  memset (unsigned long long,int /*<<< orphan*/ ,int) ; 

int iwl_pcie_alloc_ict(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	trans_pcie->ict_tbl =
		dma_alloc_coherent(trans->dev, ICT_SIZE,
				   &trans_pcie->ict_tbl_dma,
				   GFP_KERNEL);
	if (!trans_pcie->ict_tbl)
		return -ENOMEM;

	/* just an API sanity check ... it is guaranteed to be aligned */
	if (WARN_ON(trans_pcie->ict_tbl_dma & (ICT_SIZE - 1))) {
		iwl_pcie_free_ict(trans);
		return -EINVAL;
	}

	IWL_DEBUG_ISR(trans, "ict dma addr %Lx\n",
		      (unsigned long long)trans_pcie->ict_tbl_dma);

	IWL_DEBUG_ISR(trans, "ict vir addr %p\n", trans_pcie->ict_tbl);

	/* reset table and index to all 0 */
	memset(trans_pcie->ict_tbl, 0, ICT_SIZE);
	trans_pcie->ict_index = 0;

	/* add periodic RX interrupt */
	trans_pcie->inta_mask |= CSR_INT_BIT_RX_PERIODIC;
	return 0;
}