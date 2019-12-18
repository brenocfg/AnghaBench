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
struct iwl_trans {int /*<<< orphan*/  dev; } ;
struct iwl_tfd {int /*<<< orphan*/  num_tbs; } ;
struct iwl_cmd_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int) ; 
 int IWL_NUM_OF_TBS ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_pcie_tfd_get_num_tbs (struct iwl_tfd*) ; 
 int /*<<< orphan*/  iwl_pcie_tfd_tb_get_addr (struct iwl_tfd*,int) ; 
 int /*<<< orphan*/  iwl_pcie_tfd_tb_get_len (struct iwl_tfd*,int) ; 

__attribute__((used)) static void iwl_pcie_tfd_unmap(struct iwl_trans *trans,
			       struct iwl_cmd_meta *meta,
			       struct iwl_tfd *tfd)
{
	int i;
	int num_tbs;

	/* Sanity check on number of chunks */
	num_tbs = iwl_pcie_tfd_get_num_tbs(tfd);

	if (num_tbs >= IWL_NUM_OF_TBS) {
		IWL_ERR(trans, "Too many chunks: %i\n", num_tbs);
		/* @todo issue fatal error, it is quite serious situation */
		return;
	}

	/* first TB is never freed - it's the scratchbuf data */

	for (i = 1; i < num_tbs; i++)
		dma_unmap_single(trans->dev, iwl_pcie_tfd_tb_get_addr(tfd, i),
				 iwl_pcie_tfd_tb_get_len(tfd, i),
				 DMA_TO_DEVICE);

	tfd->num_tbs = 0;
}