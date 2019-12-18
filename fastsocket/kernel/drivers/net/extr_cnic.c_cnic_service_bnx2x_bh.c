#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ sw_prod_idx; int /*<<< orphan*/  io_addr; } ;
struct cnic_local {int /*<<< orphan*/  bnx2x_igu_sb_id; TYPE_1__ kcq2; int /*<<< orphan*/  (* arm_int ) (struct cnic_dev*,scalar_t__) ;TYPE_1__ kcq1; } ;
struct cnic_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int /*<<< orphan*/  CNIC_SUPPORTS_FCOE (struct bnx2x*) ; 
 int /*<<< orphan*/  CNIC_WR16 (struct cnic_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IGU_INT_ENABLE ; 
 int /*<<< orphan*/  IGU_SEG_ACCESS_DEF ; 
 scalar_t__ MAX_KCQ_IDX ; 
 int /*<<< orphan*/  cnic_ack_igu_sb (struct cnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cnic_service_bnx2x_kcq (struct cnic_dev*,TYPE_1__*) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cnic_dev*,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cnic_service_bnx2x_bh(unsigned long data)
{
	struct cnic_dev *dev = (struct cnic_dev *) data;
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	u32 status_idx, new_status_idx;

	if (unlikely(!test_bit(CNIC_F_CNIC_UP, &dev->flags)))
		return;

	while (1) {
		status_idx = cnic_service_bnx2x_kcq(dev, &cp->kcq1);

		CNIC_WR16(dev, cp->kcq1.io_addr,
			  cp->kcq1.sw_prod_idx + MAX_KCQ_IDX);

		if (!CNIC_SUPPORTS_FCOE(bp)) {
			cp->arm_int(dev, status_idx);
			break;
		}

		new_status_idx = cnic_service_bnx2x_kcq(dev, &cp->kcq2);

		if (new_status_idx != status_idx)
			continue;

		CNIC_WR16(dev, cp->kcq2.io_addr, cp->kcq2.sw_prod_idx +
			  MAX_KCQ_IDX);

		cnic_ack_igu_sb(dev, cp->bnx2x_igu_sb_id, IGU_SEG_ACCESS_DEF,
				status_idx, IGU_INT_ENABLE, 1);

		break;
	}
}