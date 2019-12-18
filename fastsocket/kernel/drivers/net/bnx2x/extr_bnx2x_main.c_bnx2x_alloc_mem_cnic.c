#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct host_hc_status_block_e2 {int dummy; } ;
struct host_hc_status_block_e1x {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * addr_drv_info_to_mcp; } ;
struct TYPE_6__ {int /*<<< orphan*/  e1x_sb; int /*<<< orphan*/  e2_sb; } ;
struct bnx2x {TYPE_2__* slowpath; TYPE_1__ cnic_eth_dev; int /*<<< orphan*/  t2_mapping; int /*<<< orphan*/  t2; int /*<<< orphan*/  cnic_sb_mapping; TYPE_3__ cnic_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  drv_info_to_mcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_PCI_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CONFIGURE_NIC_MODE (struct bnx2x*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ILT_MEMOP_ALLOC ; 
 int SRC_T2_SZ ; 
 int /*<<< orphan*/  bnx2x_free_mem_cnic (struct bnx2x*) ; 
 scalar_t__ bnx2x_ilt_mem_op_cnic (struct bnx2x*,int /*<<< orphan*/ ) ; 

int bnx2x_alloc_mem_cnic(struct bnx2x *bp)
{
	if (!CHIP_IS_E1x(bp))
		/* size = the status block + ramrod buffers */
		BNX2X_PCI_ALLOC(bp->cnic_sb.e2_sb, &bp->cnic_sb_mapping,
				sizeof(struct host_hc_status_block_e2));
	else
		BNX2X_PCI_ALLOC(bp->cnic_sb.e1x_sb,
				&bp->cnic_sb_mapping,
				sizeof(struct
				       host_hc_status_block_e1x));

	if (CONFIGURE_NIC_MODE(bp) && !bp->t2)
		/* allocate searcher T2 table, as it wasn't allocated before */
		BNX2X_PCI_ALLOC(bp->t2, &bp->t2_mapping, SRC_T2_SZ);

	/* write address to which L5 should insert its values */
	bp->cnic_eth_dev.addr_drv_info_to_mcp =
		&bp->slowpath->drv_info_to_mcp;

	if (bnx2x_ilt_mem_op_cnic(bp, ILT_MEMOP_ALLOC))
		goto alloc_mem_err;

	return 0;

alloc_mem_err:
	bnx2x_free_mem_cnic(bp);
	BNX2X_ERR("Can't allocate memory\n");
	return -ENOMEM;
}