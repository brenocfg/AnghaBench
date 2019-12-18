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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int max_send_sge; int max_srq_sge; int max_ord_per_qp; int max_ird_per_qp; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_rqe; scalar_t__ max_qp; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_wqe; int /*<<< orphan*/ * fw_ver; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct ocrdma_dev {TYPE_3__ attr; TYPE_2__ nic_info; } ;
struct ib_device_attr {unsigned long long max_mr_size; int page_size_cap; int device_cap_flags; int max_qp_init_rd_atom; int max_srq_sge; int max_pkeys; scalar_t__ max_fast_reg_page_list_len; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_srq_wr; scalar_t__ max_srq; void* max_qp_rd_atom; scalar_t__ max_map_per_fmr; scalar_t__ max_fmr; scalar_t__ atomic_cap; int /*<<< orphan*/  max_pd; scalar_t__ max_mw; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; scalar_t__ max_sge_rd; void* max_sge; int /*<<< orphan*/  max_qp_wr; scalar_t__ max_ah; scalar_t__ max_qp; scalar_t__ hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  fw_ver; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int IB_DEVICE_CURR_QP_STATE_MOD ; 
 int IB_DEVICE_LOCAL_DMA_LKEY ; 
 int IB_DEVICE_RC_RNR_NAK_GEN ; 
 int IB_DEVICE_SHUTDOWN_PORT ; 
 int IB_DEVICE_SYS_IMAGE_GUID ; 
 struct ocrdma_dev* get_ocrdma_dev (struct ib_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memset (struct ib_device_attr*,int /*<<< orphan*/ ,int) ; 
 void* min (int,int) ; 
 int /*<<< orphan*/  ocrdma_get_guid (struct ocrdma_dev*,int /*<<< orphan*/ *) ; 

int ocrdma_query_device(struct ib_device *ibdev, struct ib_device_attr *attr)
{
	struct ocrdma_dev *dev = get_ocrdma_dev(ibdev);

	memset(attr, 0, sizeof *attr);
	memcpy(&attr->fw_ver, &dev->attr.fw_ver[0],
	       min(sizeof(dev->attr.fw_ver), sizeof(attr->fw_ver)));
	ocrdma_get_guid(dev, (u8 *)&attr->sys_image_guid);
	attr->max_mr_size = ~0ull;
	attr->page_size_cap = 0xffff000;
	attr->vendor_id = dev->nic_info.pdev->vendor;
	attr->vendor_part_id = dev->nic_info.pdev->device;
	attr->hw_ver = 0;
	attr->max_qp = dev->attr.max_qp;
	attr->max_ah = dev->attr.max_qp;
	attr->max_qp_wr = dev->attr.max_wqe;

	attr->device_cap_flags = IB_DEVICE_CURR_QP_STATE_MOD |
					IB_DEVICE_RC_RNR_NAK_GEN |
					IB_DEVICE_SHUTDOWN_PORT |
					IB_DEVICE_SYS_IMAGE_GUID |
					IB_DEVICE_LOCAL_DMA_LKEY;
	attr->max_sge = min(dev->attr.max_send_sge, dev->attr.max_srq_sge);
	attr->max_sge_rd = 0;
	attr->max_cq = dev->attr.max_cq;
	attr->max_cqe = dev->attr.max_cqe;
	attr->max_mr = dev->attr.max_mr;
	attr->max_mw = 0;
	attr->max_pd = dev->attr.max_pd;
	attr->atomic_cap = 0;
	attr->max_fmr = 0;
	attr->max_map_per_fmr = 0;
	attr->max_qp_rd_atom =
	    min(dev->attr.max_ord_per_qp, dev->attr.max_ird_per_qp);
	attr->max_qp_init_rd_atom = dev->attr.max_ord_per_qp;
	attr->max_srq = (dev->attr.max_qp - 1);
	attr->max_srq_sge = dev->attr.max_srq_sge;
	attr->max_srq_wr = dev->attr.max_rqe;
	attr->local_ca_ack_delay = dev->attr.local_ca_ack_delay;
	attr->max_fast_reg_page_list_len = 0;
	attr->max_pkeys = 1;
	return 0;
}