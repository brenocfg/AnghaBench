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
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct ib_smp {scalar_t__ data; int /*<<< orphan*/  attr_id; } ;
struct ib_device_attr {int device_cap_flags; int vendor_id; int hw_ver; unsigned long long max_mr_size; int max_qp; int max_qp_rd_atom; int max_res_rd_atom; int max_mcast_grp; int max_mcast_qp_attach; int max_total_mcast_qp_attach; int /*<<< orphan*/  max_map_per_fmr; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  masked_atomic_cap; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_fast_reg_page_list_len; int /*<<< orphan*/  max_srq_sge; scalar_t__ max_srq_wr; scalar_t__ max_srq; int /*<<< orphan*/  max_qp_init_rd_atom; scalar_t__ max_pd; scalar_t__ max_mr; int /*<<< orphan*/  max_cqe; scalar_t__ max_cq; int /*<<< orphan*/  max_sge; scalar_t__ max_qp_wr; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  fw_ver; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int flags; int bmme_flags; int num_qps; int reserved_qps; int max_qp_dest_rdma; int num_mgms; int num_amgms; int num_qp_per_mgm; int /*<<< orphan*/  max_fmr_maps; int /*<<< orphan*/ * pkey_table_len; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_srq_sge; scalar_t__ max_srq_wqes; scalar_t__ reserved_srqs; scalar_t__ num_srqs; int /*<<< orphan*/  max_qp_init_rdma; scalar_t__ reserved_pds; scalar_t__ num_pds; scalar_t__ reserved_mrws; scalar_t__ num_mpts; int /*<<< orphan*/  max_cqes; scalar_t__ reserved_cqs; scalar_t__ num_cqs; int /*<<< orphan*/  max_rq_sg; int /*<<< orphan*/  max_sq_sg; scalar_t__ max_wqes; int /*<<< orphan*/  page_size_cap; scalar_t__ max_gso_sz; int /*<<< orphan*/  fw_ver; } ;
struct TYPE_5__ {TYPE_3__ caps; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_ATOMIC_HCA ; 
 int /*<<< orphan*/  IB_ATOMIC_NONE ; 
 int IB_DEVICE_AUTO_PATH_MIG ; 
 int IB_DEVICE_BAD_PKEY_CNTR ; 
 int IB_DEVICE_BAD_QKEY_CNTR ; 
 int IB_DEVICE_BLOCK_MULTICAST_LOOPBACK ; 
 int IB_DEVICE_CHANGE_PHY_PORT ; 
 int IB_DEVICE_LOCAL_DMA_LKEY ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int IB_DEVICE_MEM_WINDOW ; 
 int IB_DEVICE_MEM_WINDOW_TYPE_2A ; 
 int IB_DEVICE_MEM_WINDOW_TYPE_2B ; 
 int IB_DEVICE_PORT_ACTIVE_EVENT ; 
 int IB_DEVICE_RC_RNR_NAK_GEN ; 
 int IB_DEVICE_SYS_IMAGE_GUID ; 
 int IB_DEVICE_UD_AV_PORT_ENFORCE ; 
 int IB_DEVICE_UD_IP_CSUM ; 
 int IB_DEVICE_UD_TSO ; 
 int IB_DEVICE_XRC ; 
 int /*<<< orphan*/  IB_SMP_ATTR_NODE_INFO ; 
 int MLX4_BMME_FLAG_FAST_REG_WR ; 
 int MLX4_BMME_FLAG_LOCAL_INV ; 
 int MLX4_BMME_FLAG_REMOTE_INV ; 
 int MLX4_BMME_FLAG_RESERVED_LKEY ; 
 int MLX4_BMME_FLAG_TYPE_2_WIN ; 
 int MLX4_BMME_FLAG_WIN_TYPE_2B ; 
 int MLX4_DEV_CAP_FLAG_APM ; 
 int MLX4_DEV_CAP_FLAG_ATOMIC ; 
 int MLX4_DEV_CAP_FLAG_BAD_PKEY_CNTR ; 
 int MLX4_DEV_CAP_FLAG_BAD_QKEY_CNTR ; 
 int MLX4_DEV_CAP_FLAG_BLH ; 
 int MLX4_DEV_CAP_FLAG_IPOIB_CSUM ; 
 int MLX4_DEV_CAP_FLAG_MEM_WINDOW ; 
 int MLX4_DEV_CAP_FLAG_UD_AV_PORT ; 
 int MLX4_DEV_CAP_FLAG_XRC ; 
 scalar_t__ MLX4_IB_SQ_MAX_SPARE ; 
 int /*<<< orphan*/  MLX4_MAD_IFC_IGNORE_KEYS ; 
 int /*<<< orphan*/  MLX4_MAX_FAST_REG_PAGES ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct ib_device_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_MAD_IFC (struct mlx4_ib_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mlx4_ib_query_device(struct ib_device *ibdev,
				struct ib_device_attr *props)
{
	struct mlx4_ib_dev *dev = to_mdev(ibdev);
	struct ib_smp *in_mad  = NULL;
	struct ib_smp *out_mad = NULL;
	int err = -ENOMEM;

	in_mad  = kzalloc(sizeof *in_mad, GFP_KERNEL);
	out_mad = kmalloc(sizeof *out_mad, GFP_KERNEL);
	if (!in_mad || !out_mad)
		goto out;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mlx4_MAD_IFC(to_mdev(ibdev), MLX4_MAD_IFC_IGNORE_KEYS,
			   1, NULL, NULL, in_mad, out_mad);
	if (err)
		goto out;

	memset(props, 0, sizeof *props);

	props->fw_ver = dev->dev->caps.fw_ver;
	props->device_cap_flags    = IB_DEVICE_CHANGE_PHY_PORT |
		IB_DEVICE_PORT_ACTIVE_EVENT		|
		IB_DEVICE_SYS_IMAGE_GUID		|
		IB_DEVICE_RC_RNR_NAK_GEN		|
		IB_DEVICE_BLOCK_MULTICAST_LOOPBACK;
	if (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_BAD_PKEY_CNTR)
		props->device_cap_flags |= IB_DEVICE_BAD_PKEY_CNTR;
	if (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_BAD_QKEY_CNTR)
		props->device_cap_flags |= IB_DEVICE_BAD_QKEY_CNTR;
	if (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_APM)
		props->device_cap_flags |= IB_DEVICE_AUTO_PATH_MIG;
	if (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_UD_AV_PORT)
		props->device_cap_flags |= IB_DEVICE_UD_AV_PORT_ENFORCE;
	if (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_IPOIB_CSUM)
		props->device_cap_flags |= IB_DEVICE_UD_IP_CSUM;
	if (dev->dev->caps.max_gso_sz && dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_BLH)
		props->device_cap_flags |= IB_DEVICE_UD_TSO;
	if (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_RESERVED_LKEY)
		props->device_cap_flags |= IB_DEVICE_LOCAL_DMA_LKEY;
	if ((dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_LOCAL_INV) &&
	    (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_REMOTE_INV) &&
	    (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_FAST_REG_WR))
		props->device_cap_flags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
	if (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_XRC)
		props->device_cap_flags |= IB_DEVICE_XRC;
	if (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_MEM_WINDOW)
		props->device_cap_flags |= IB_DEVICE_MEM_WINDOW;
	if (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_TYPE_2_WIN) {
		if (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_WIN_TYPE_2B)
			props->device_cap_flags |= IB_DEVICE_MEM_WINDOW_TYPE_2B;
		else
			props->device_cap_flags |= IB_DEVICE_MEM_WINDOW_TYPE_2A;
	}

	props->vendor_id	   = be32_to_cpup((__be32 *) (out_mad->data + 36)) &
		0xffffff;
	props->vendor_part_id	   = dev->dev->pdev->device;
	props->hw_ver		   = be32_to_cpup((__be32 *) (out_mad->data + 32));
	memcpy(&props->sys_image_guid, out_mad->data +	4, 8);

	props->max_mr_size	   = ~0ull;
	props->page_size_cap	   = dev->dev->caps.page_size_cap;
	props->max_qp		   = dev->dev->caps.num_qps - dev->dev->caps.reserved_qps;
	props->max_qp_wr	   = dev->dev->caps.max_wqes - MLX4_IB_SQ_MAX_SPARE;
	props->max_sge		   = min(dev->dev->caps.max_sq_sg,
					 dev->dev->caps.max_rq_sg);
	props->max_cq		   = dev->dev->caps.num_cqs - dev->dev->caps.reserved_cqs;
	props->max_cqe		   = dev->dev->caps.max_cqes;
	props->max_mr		   = dev->dev->caps.num_mpts - dev->dev->caps.reserved_mrws;
	props->max_pd		   = dev->dev->caps.num_pds - dev->dev->caps.reserved_pds;
	props->max_qp_rd_atom	   = dev->dev->caps.max_qp_dest_rdma;
	props->max_qp_init_rd_atom = dev->dev->caps.max_qp_init_rdma;
	props->max_res_rd_atom	   = props->max_qp_rd_atom * props->max_qp;
	props->max_srq		   = dev->dev->caps.num_srqs - dev->dev->caps.reserved_srqs;
	props->max_srq_wr	   = dev->dev->caps.max_srq_wqes - 1;
	props->max_srq_sge	   = dev->dev->caps.max_srq_sge;
	props->max_fast_reg_page_list_len = MLX4_MAX_FAST_REG_PAGES;
	props->local_ca_ack_delay  = dev->dev->caps.local_ca_ack_delay;
	props->atomic_cap	   = dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_ATOMIC ?
		IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	props->masked_atomic_cap   = props->atomic_cap;
	props->max_pkeys	   = dev->dev->caps.pkey_table_len[1];
	props->max_mcast_grp	   = dev->dev->caps.num_mgms + dev->dev->caps.num_amgms;
	props->max_mcast_qp_attach = dev->dev->caps.num_qp_per_mgm;
	props->max_total_mcast_qp_attach = props->max_mcast_qp_attach *
					   props->max_mcast_grp;
	props->max_map_per_fmr = dev->dev->caps.max_fmr_maps;

out:
	kfree(in_mad);
	kfree(out_mad);

	return err;
}