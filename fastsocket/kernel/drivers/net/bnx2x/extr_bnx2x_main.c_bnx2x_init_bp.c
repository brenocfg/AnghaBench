#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int expires; unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_6__ {int /*<<< orphan*/  phy_mutex; } ;
struct bnx2x {int fw_seq; int disable_tpa; int flags; int dropless_fc; int rx_csum; int tx_ticks; int rx_ticks; int current_interval; int max_cos; int min_msix_vec_cnt; int dump_preset_idx; int /*<<< orphan*/  cnic_base_cl_id; TYPE_4__ timer; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  mrrs; TYPE_3__* dev; TYPE_2__* pdev; int /*<<< orphan*/  period_task; int /*<<< orphan*/  sp_rtnl_task; int /*<<< orphan*/  sp_task; int /*<<< orphan*/  stats_sema; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  fw_mb_mutex; TYPE_1__ port; } ;
struct TYPE_10__ {int /*<<< orphan*/  drv_mb_header; } ;
struct TYPE_8__ {int /*<<< orphan*/  features; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2X_BTR ; 
 int /*<<< orphan*/  BNX2X_DCBX_ENABLED_OFF ; 
 int /*<<< orphan*/  BNX2X_DCBX_ENABLED_ON_NEG_ON ; 
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,int) ; 
 int BP_FUNC (struct bnx2x*) ; 
 size_t BP_FW_MB_IDX (struct bnx2x*) ; 
 scalar_t__ BP_NOMCP (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_FPGA (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 scalar_t__ CNIC_SUPPORT (struct bnx2x*) ; 
 int DRV_MSG_SEQ_NUMBER_MASK ; 
 int /*<<< orphan*/  FP_SB_MAX_E1x ; 
 int /*<<< orphan*/  FP_SB_MAX_E2 ; 
 int GRO_ENABLE_FLAG ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_MF_FCOE_AFEX (struct bnx2x*) ; 
 scalar_t__ IS_MF_STORAGE_SD (struct bnx2x*) ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int /*<<< orphan*/  MAX_RX_AVAIL ; 
 int /*<<< orphan*/  MAX_TX_AVAIL ; 
 int /*<<< orphan*/  NETIF_F_GRO ; 
 int /*<<< orphan*/  NETIF_F_LRO ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ SHMEM2_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int TPA_ENABLE_FLAG ; 
 int bnx2x_alloc_mem_bp (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dcbx_init_params (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dcbx_set_state (struct bnx2x*,int,int /*<<< orphan*/ ) ; 
 int bnx2x_get_dropless_info (struct bnx2x*) ; 
 int bnx2x_get_hwinfo (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_period_task ; 
 int /*<<< orphan*/  bnx2x_prev_unload (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_read_fwinfo (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_modes_bitmap (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_sp_rtnl_task ; 
 int /*<<< orphan*/  bnx2x_sp_task ; 
 int /*<<< orphan*/  bnx2x_timer ; 
 int /*<<< orphan*/  dcbx_lldp_dcbx_stat_offset ; 
 int /*<<< orphan*/  dcbx_lldp_params_offset ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int disable_tpa ; 
 int dropless_fc ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 TYPE_5__* func_mb ; 
 int /*<<< orphan*/  init_timer (TYPE_4__*) ; 
 int jiffies ; 
 int /*<<< orphan*/  mrrs ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_init_bp(struct bnx2x *bp)
{
	int func;
	int rc;

	mutex_init(&bp->port.phy_mutex);
	mutex_init(&bp->fw_mb_mutex);
	spin_lock_init(&bp->stats_lock);
	sema_init(&bp->stats_sema, 1);

	INIT_DELAYED_WORK(&bp->sp_task, bnx2x_sp_task);
	INIT_DELAYED_WORK(&bp->sp_rtnl_task, bnx2x_sp_rtnl_task);
	INIT_DELAYED_WORK(&bp->period_task, bnx2x_period_task);
	if (IS_PF(bp)) {
		rc = bnx2x_get_hwinfo(bp);
		if (rc)
			return rc;
	} else {
		eth_zero_addr(bp->dev->dev_addr);
	}

	bnx2x_set_modes_bitmap(bp);

	rc = bnx2x_alloc_mem_bp(bp);
	if (rc)
		return rc;

	bnx2x_read_fwinfo(bp);

	func = BP_FUNC(bp);

	/* need to reset chip if undi was active */
	if (IS_PF(bp) && !BP_NOMCP(bp)) {
		/* init fw_seq */
		bp->fw_seq =
			SHMEM_RD(bp, func_mb[BP_FW_MB_IDX(bp)].drv_mb_header) &
							DRV_MSG_SEQ_NUMBER_MASK;
		BNX2X_DEV_INFO("fw_seq 0x%08x\n", bp->fw_seq);

		bnx2x_prev_unload(bp);
	}

	if (CHIP_REV_IS_FPGA(bp))
		dev_err(&bp->pdev->dev, "FPGA detected\n");

	if (BP_NOMCP(bp) && (func == 0))
		dev_err(&bp->pdev->dev, "MCP disabled, must load devices in order!\n");

	bp->dev->features |= NETIF_F_GRO;

	bp->disable_tpa = disable_tpa;
	bp->disable_tpa |= IS_MF_STORAGE_SD(bp) || IS_MF_FCOE_AFEX(bp);

	/* Set TPA flags */
	if (bp->disable_tpa) {
		bp->flags &= ~(TPA_ENABLE_FLAG | GRO_ENABLE_FLAG);
		bp->dev->features &= ~NETIF_F_LRO;
	} else {
		/* RHEL6.3: don't enable GRO_ENABLE_FLAG yet */
		bp->flags |= TPA_ENABLE_FLAG;
		bp->dev->features |= NETIF_F_LRO;
	}

	if (CHIP_IS_E1(bp))
		bp->dropless_fc = 0;
	else
		bp->dropless_fc = dropless_fc | bnx2x_get_dropless_info(bp);

	bp->mrrs = mrrs;

	bp->tx_ring_size = IS_MF_FCOE_AFEX(bp) ? 0 : MAX_TX_AVAIL;
	if (IS_VF(bp))
		bp->rx_ring_size = MAX_RX_AVAIL;

	bp->rx_csum = 1;

	/* make sure that the numbers are in the right granularity */
	bp->tx_ticks = (50 / BNX2X_BTR) * BNX2X_BTR;
	bp->rx_ticks = (25 / BNX2X_BTR) * BNX2X_BTR;

	bp->current_interval = CHIP_REV_IS_SLOW(bp) ? 5*HZ : HZ;

	init_timer(&bp->timer);
	bp->timer.expires = jiffies + bp->current_interval;
	bp->timer.data = (unsigned long) bp;
	bp->timer.function = bnx2x_timer;

	if (SHMEM2_HAS(bp, dcbx_lldp_params_offset) &&
	    SHMEM2_HAS(bp, dcbx_lldp_dcbx_stat_offset) &&
	    SHMEM2_RD(bp, dcbx_lldp_params_offset) &&
	    SHMEM2_RD(bp, dcbx_lldp_dcbx_stat_offset)) {
		bnx2x_dcbx_set_state(bp, true, BNX2X_DCBX_ENABLED_ON_NEG_ON);
		bnx2x_dcbx_init_params(bp);
	} else {
		bnx2x_dcbx_set_state(bp, false, BNX2X_DCBX_ENABLED_OFF);
	}

	if (CHIP_IS_E1x(bp))
		bp->cnic_base_cl_id = FP_SB_MAX_E1x;
	else
		bp->cnic_base_cl_id = FP_SB_MAX_E2;

	bp->max_cos = 1;

	/* We need at least one default status block for slow-path events,
	 * second status block for the L2 queue, and a third status block for
	 * CNIC if supported.
	 */
	if (CNIC_SUPPORT(bp))
		bp->min_msix_vec_cnt = 3;
	else
		bp->min_msix_vec_cnt = 2;
	BNX2X_DEV_INFO("bp->min_msix_vec_cnt %d", bp->min_msix_vec_cnt);

	bp->dump_preset_idx = 1;

	return rc;
}