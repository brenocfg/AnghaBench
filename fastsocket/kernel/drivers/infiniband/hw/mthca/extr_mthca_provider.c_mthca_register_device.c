#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long long uverbs_cmd_mask; int num_comp_vectors; int /*<<< orphan*/  dev; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  process_mad; int /*<<< orphan*/  detach_mcast; int /*<<< orphan*/  attach_mcast; int /*<<< orphan*/  map_phys_fmr; int /*<<< orphan*/  dealloc_fmr; int /*<<< orphan*/  unmap_fmr; int /*<<< orphan*/  alloc_fmr; int /*<<< orphan*/  dereg_mr; int /*<<< orphan*/  reg_user_mr; int /*<<< orphan*/  reg_phys_mr; int /*<<< orphan*/  get_dma_mr; int /*<<< orphan*/  poll_cq; int /*<<< orphan*/  destroy_cq; int /*<<< orphan*/  resize_cq; int /*<<< orphan*/  create_cq; int /*<<< orphan*/  destroy_qp; int /*<<< orphan*/  query_qp; int /*<<< orphan*/  modify_qp; int /*<<< orphan*/  create_qp; int /*<<< orphan*/  post_srq_recv; int /*<<< orphan*/  destroy_srq; int /*<<< orphan*/  query_srq; int /*<<< orphan*/  modify_srq; int /*<<< orphan*/  create_srq; int /*<<< orphan*/  destroy_ah; int /*<<< orphan*/  query_ah; int /*<<< orphan*/  create_ah; int /*<<< orphan*/  dealloc_pd; int /*<<< orphan*/  alloc_pd; int /*<<< orphan*/  mmap; int /*<<< orphan*/  dealloc_ucontext; int /*<<< orphan*/  alloc_ucontext; int /*<<< orphan*/  query_gid; int /*<<< orphan*/  query_pkey; int /*<<< orphan*/  modify_port; int /*<<< orphan*/  modify_device; int /*<<< orphan*/  query_port; int /*<<< orphan*/  query_device; int /*<<< orphan*/ * dma_device; int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  node_type; int /*<<< orphan*/  uverbs_abi_ver; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_ports; } ;
struct mthca_dev {int mthca_flags; TYPE_3__ ib_dev; int /*<<< orphan*/  cap_mask_mutex; TYPE_2__* pdev; TYPE_1__ limits; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IB_DEVICE_NAME_MAX ; 
 unsigned long long IB_USER_VERBS_CMD_ALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_ATTACH_MCAST ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_QP ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_DEREG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_DETACH_MCAST ; 
 unsigned long long IB_USER_VERBS_CMD_GET_CONTEXT ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_DEVICE ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_PORT ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_SRQ ; 
 unsigned long long IB_USER_VERBS_CMD_REG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_RESIZE_CQ ; 
 int MTHCA_FLAG_FMR ; 
 int MTHCA_FLAG_SRQ ; 
 int /*<<< orphan*/  MTHCA_UVERBS_ABI_VERSION ; 
 int /*<<< orphan*/  RDMA_NODE_IB_CA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ib_register_device (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (TYPE_3__*) ; 
 int /*<<< orphan*/  mthca_ah_create ; 
 int /*<<< orphan*/  mthca_ah_destroy ; 
 int /*<<< orphan*/  mthca_ah_query ; 
 int /*<<< orphan*/  mthca_alloc_fmr ; 
 int /*<<< orphan*/  mthca_alloc_pd ; 
 int /*<<< orphan*/  mthca_alloc_ucontext ; 
 int /*<<< orphan*/  mthca_arbel_arm_cq ; 
 int /*<<< orphan*/  mthca_arbel_map_phys_fmr ; 
 int /*<<< orphan*/  mthca_arbel_post_receive ; 
 int /*<<< orphan*/  mthca_arbel_post_send ; 
 int /*<<< orphan*/  mthca_arbel_post_srq_recv ; 
 int /*<<< orphan*/  mthca_create_cq ; 
 int /*<<< orphan*/  mthca_create_qp ; 
 int /*<<< orphan*/  mthca_create_srq ; 
 int /*<<< orphan*/  mthca_dealloc_fmr ; 
 int /*<<< orphan*/  mthca_dealloc_pd ; 
 int /*<<< orphan*/  mthca_dealloc_ucontext ; 
 int /*<<< orphan*/  mthca_dereg_mr ; 
 int /*<<< orphan*/  mthca_destroy_cq ; 
 int /*<<< orphan*/  mthca_destroy_qp ; 
 int /*<<< orphan*/  mthca_destroy_srq ; 
 int /*<<< orphan*/ * mthca_dev_attributes ; 
 int /*<<< orphan*/  mthca_get_dma_mr ; 
 int mthca_init_node_data (struct mthca_dev*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_mmap_uar ; 
 int /*<<< orphan*/  mthca_modify_device ; 
 int /*<<< orphan*/  mthca_modify_port ; 
 int /*<<< orphan*/  mthca_modify_qp ; 
 int /*<<< orphan*/  mthca_modify_srq ; 
 int /*<<< orphan*/  mthca_multicast_attach ; 
 int /*<<< orphan*/  mthca_multicast_detach ; 
 int /*<<< orphan*/  mthca_poll_cq ; 
 int /*<<< orphan*/  mthca_process_mad ; 
 int /*<<< orphan*/  mthca_query_device ; 
 int /*<<< orphan*/  mthca_query_gid ; 
 int /*<<< orphan*/  mthca_query_pkey ; 
 int /*<<< orphan*/  mthca_query_port ; 
 int /*<<< orphan*/  mthca_query_qp ; 
 int /*<<< orphan*/  mthca_query_srq ; 
 int /*<<< orphan*/  mthca_reg_phys_mr ; 
 int /*<<< orphan*/  mthca_reg_user_mr ; 
 int /*<<< orphan*/  mthca_resize_cq ; 
 int /*<<< orphan*/  mthca_start_catas_poll (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_tavor_arm_cq ; 
 int /*<<< orphan*/  mthca_tavor_map_phys_fmr ; 
 int /*<<< orphan*/  mthca_tavor_post_receive ; 
 int /*<<< orphan*/  mthca_tavor_post_send ; 
 int /*<<< orphan*/  mthca_tavor_post_srq_recv ; 
 int /*<<< orphan*/  mthca_unmap_fmr ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int mthca_register_device(struct mthca_dev *dev)
{
	int ret;
	int i;

	ret = mthca_init_node_data(dev);
	if (ret)
		return ret;

	strlcpy(dev->ib_dev.name, "mthca%d", IB_DEVICE_NAME_MAX);
	dev->ib_dev.owner                = THIS_MODULE;

	dev->ib_dev.uverbs_abi_ver	 = MTHCA_UVERBS_ABI_VERSION;
	dev->ib_dev.uverbs_cmd_mask	 =
		(1ull << IB_USER_VERBS_CMD_GET_CONTEXT)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_DEVICE)	|
		(1ull << IB_USER_VERBS_CMD_QUERY_PORT)		|
		(1ull << IB_USER_VERBS_CMD_ALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_DEALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_REG_MR)		|
		(1ull << IB_USER_VERBS_CMD_DEREG_MR)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL)	|
		(1ull << IB_USER_VERBS_CMD_CREATE_CQ)		|
		(1ull << IB_USER_VERBS_CMD_RESIZE_CQ)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_CQ)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_QP)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_QP)		|
		(1ull << IB_USER_VERBS_CMD_MODIFY_QP)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_QP)		|
		(1ull << IB_USER_VERBS_CMD_ATTACH_MCAST)	|
		(1ull << IB_USER_VERBS_CMD_DETACH_MCAST);
	dev->ib_dev.node_type            = RDMA_NODE_IB_CA;
	dev->ib_dev.phys_port_cnt        = dev->limits.num_ports;
	dev->ib_dev.num_comp_vectors     = 1;
	dev->ib_dev.dma_device           = &dev->pdev->dev;
	dev->ib_dev.query_device         = mthca_query_device;
	dev->ib_dev.query_port           = mthca_query_port;
	dev->ib_dev.modify_device        = mthca_modify_device;
	dev->ib_dev.modify_port          = mthca_modify_port;
	dev->ib_dev.query_pkey           = mthca_query_pkey;
	dev->ib_dev.query_gid            = mthca_query_gid;
	dev->ib_dev.alloc_ucontext       = mthca_alloc_ucontext;
	dev->ib_dev.dealloc_ucontext     = mthca_dealloc_ucontext;
	dev->ib_dev.mmap                 = mthca_mmap_uar;
	dev->ib_dev.alloc_pd             = mthca_alloc_pd;
	dev->ib_dev.dealloc_pd           = mthca_dealloc_pd;
	dev->ib_dev.create_ah            = mthca_ah_create;
	dev->ib_dev.query_ah             = mthca_ah_query;
	dev->ib_dev.destroy_ah           = mthca_ah_destroy;

	if (dev->mthca_flags & MTHCA_FLAG_SRQ) {
		dev->ib_dev.create_srq           = mthca_create_srq;
		dev->ib_dev.modify_srq           = mthca_modify_srq;
		dev->ib_dev.query_srq            = mthca_query_srq;
		dev->ib_dev.destroy_srq          = mthca_destroy_srq;
		dev->ib_dev.uverbs_cmd_mask	|=
			(1ull << IB_USER_VERBS_CMD_CREATE_SRQ)		|
			(1ull << IB_USER_VERBS_CMD_MODIFY_SRQ)		|
			(1ull << IB_USER_VERBS_CMD_QUERY_SRQ)		|
			(1ull << IB_USER_VERBS_CMD_DESTROY_SRQ);

		if (mthca_is_memfree(dev))
			dev->ib_dev.post_srq_recv = mthca_arbel_post_srq_recv;
		else
			dev->ib_dev.post_srq_recv = mthca_tavor_post_srq_recv;
	}

	dev->ib_dev.create_qp            = mthca_create_qp;
	dev->ib_dev.modify_qp            = mthca_modify_qp;
	dev->ib_dev.query_qp             = mthca_query_qp;
	dev->ib_dev.destroy_qp           = mthca_destroy_qp;
	dev->ib_dev.create_cq            = mthca_create_cq;
	dev->ib_dev.resize_cq            = mthca_resize_cq;
	dev->ib_dev.destroy_cq           = mthca_destroy_cq;
	dev->ib_dev.poll_cq              = mthca_poll_cq;
	dev->ib_dev.get_dma_mr           = mthca_get_dma_mr;
	dev->ib_dev.reg_phys_mr          = mthca_reg_phys_mr;
	dev->ib_dev.reg_user_mr          = mthca_reg_user_mr;
	dev->ib_dev.dereg_mr             = mthca_dereg_mr;

	if (dev->mthca_flags & MTHCA_FLAG_FMR) {
		dev->ib_dev.alloc_fmr            = mthca_alloc_fmr;
		dev->ib_dev.unmap_fmr            = mthca_unmap_fmr;
		dev->ib_dev.dealloc_fmr          = mthca_dealloc_fmr;
		if (mthca_is_memfree(dev))
			dev->ib_dev.map_phys_fmr = mthca_arbel_map_phys_fmr;
		else
			dev->ib_dev.map_phys_fmr = mthca_tavor_map_phys_fmr;
	}

	dev->ib_dev.attach_mcast         = mthca_multicast_attach;
	dev->ib_dev.detach_mcast         = mthca_multicast_detach;
	dev->ib_dev.process_mad          = mthca_process_mad;

	if (mthca_is_memfree(dev)) {
		dev->ib_dev.req_notify_cq = mthca_arbel_arm_cq;
		dev->ib_dev.post_send     = mthca_arbel_post_send;
		dev->ib_dev.post_recv     = mthca_arbel_post_receive;
	} else {
		dev->ib_dev.req_notify_cq = mthca_tavor_arm_cq;
		dev->ib_dev.post_send     = mthca_tavor_post_send;
		dev->ib_dev.post_recv     = mthca_tavor_post_receive;
	}

	mutex_init(&dev->cap_mask_mutex);

	ret = ib_register_device(&dev->ib_dev, NULL);
	if (ret)
		return ret;

	for (i = 0; i < ARRAY_SIZE(mthca_dev_attributes); ++i) {
		ret = device_create_file(&dev->ib_dev.dev,
					 mthca_dev_attributes[i]);
		if (ret) {
			ib_unregister_device(&dev->ib_dev);
			return ret;
		}
	}

	mthca_start_catas_poll(dev);

	return 0;
}