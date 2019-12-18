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
struct TYPE_6__ {int /*<<< orphan*/  conn_and_cmd_data; } ;
struct TYPE_5__ {int type_error_flags; } ;
union eth_rx_cqe {TYPE_3__ ramrod_cqe; TYPE_2__ fast_path_cqe; } ;
typedef  int u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct cnic_uio_dev {scalar_t__ l2_ring; } ;
struct cnic_local {size_t* rx_cons_ptr; size_t rx_cons; TYPE_1__* dev; struct cnic_uio_dev* udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t BNX2X_MAX_RCQ_DESC_CNT ; 
 size_t BNX2X_NEXT_RCQE (size_t) ; 
 int BNX2_PAGE_SIZE ; 
 int /*<<< orphan*/  CNIC_F_BNX2X_CLASS ; 
 int COMMON_RAMROD_ETH_RX_CQE_CMD_ID_SHIFT ; 
 int ETH_FAST_PATH_RX_CQE_TYPE ; 
 int RAMROD_CMD_ID_ETH_CLIENT_SETUP ; 
 int RAMROD_CMD_ID_ETH_HALT ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_l2_completion(struct cnic_local *cp)
{
	u16 hw_cons, sw_cons;
	struct cnic_uio_dev *udev = cp->udev;
	union eth_rx_cqe *cqe, *cqe_ring = (union eth_rx_cqe *)
					(udev->l2_ring + (2 * BNX2_PAGE_SIZE));
	u32 cmd;
	int comp = 0;

	if (!test_bit(CNIC_F_BNX2X_CLASS, &cp->dev->flags))
		return 0;

	hw_cons = *cp->rx_cons_ptr;
	if ((hw_cons & BNX2X_MAX_RCQ_DESC_CNT) == BNX2X_MAX_RCQ_DESC_CNT)
		hw_cons++;

	sw_cons = cp->rx_cons;
	while (sw_cons != hw_cons) {
		u8 cqe_fp_flags;

		cqe = &cqe_ring[sw_cons & BNX2X_MAX_RCQ_DESC_CNT];
		cqe_fp_flags = cqe->fast_path_cqe.type_error_flags;
		if (cqe_fp_flags & ETH_FAST_PATH_RX_CQE_TYPE) {
			cmd = le32_to_cpu(cqe->ramrod_cqe.conn_and_cmd_data);
			cmd >>= COMMON_RAMROD_ETH_RX_CQE_CMD_ID_SHIFT;
			if (cmd == RAMROD_CMD_ID_ETH_CLIENT_SETUP ||
			    cmd == RAMROD_CMD_ID_ETH_HALT)
				comp++;
		}
		sw_cons = BNX2X_NEXT_RCQE(sw_cons);
	}
	return comp;
}