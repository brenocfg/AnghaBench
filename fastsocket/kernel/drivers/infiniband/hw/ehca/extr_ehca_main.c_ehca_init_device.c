#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int uverbs_abi_ver; unsigned long long uverbs_cmd_mask; int num_comp_vectors; int /*<<< orphan*/  post_srq_recv; int /*<<< orphan*/  destroy_srq; int /*<<< orphan*/  query_srq; int /*<<< orphan*/  modify_srq; int /*<<< orphan*/  create_srq; int /*<<< orphan*/ * dma_ops; int /*<<< orphan*/  mmap; int /*<<< orphan*/  process_mad; int /*<<< orphan*/  detach_mcast; int /*<<< orphan*/  attach_mcast; int /*<<< orphan*/  dealloc_fmr; int /*<<< orphan*/  unmap_fmr; int /*<<< orphan*/  map_phys_fmr; int /*<<< orphan*/  alloc_fmr; int /*<<< orphan*/  dealloc_mw; int /*<<< orphan*/  bind_mw; int /*<<< orphan*/  alloc_mw; int /*<<< orphan*/  rereg_phys_mr; int /*<<< orphan*/  dereg_mr; int /*<<< orphan*/  query_mr; int /*<<< orphan*/  reg_user_mr; int /*<<< orphan*/  reg_phys_mr; int /*<<< orphan*/  get_dma_mr; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  poll_cq; int /*<<< orphan*/  resize_cq; int /*<<< orphan*/  destroy_cq; int /*<<< orphan*/  create_cq; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  destroy_qp; int /*<<< orphan*/  query_qp; int /*<<< orphan*/  modify_qp; int /*<<< orphan*/  create_qp; int /*<<< orphan*/  destroy_ah; int /*<<< orphan*/  query_ah; int /*<<< orphan*/  create_ah; int /*<<< orphan*/  dealloc_pd; int /*<<< orphan*/  alloc_pd; int /*<<< orphan*/  dealloc_ucontext; int /*<<< orphan*/  alloc_ucontext; int /*<<< orphan*/  modify_port; int /*<<< orphan*/  query_pkey; int /*<<< orphan*/  query_gid; int /*<<< orphan*/  query_port; int /*<<< orphan*/  query_device; int /*<<< orphan*/ * dma_device; int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  node_type; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct ehca_shca {TYPE_2__ ib_device; int /*<<< orphan*/  hca_cap; TYPE_1__* ofdev; int /*<<< orphan*/  num_ports; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ EHCA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCA_CAP_SRQ ; 
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
 int /*<<< orphan*/  RDMA_NODE_IB_CA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ehca_alloc_fmr ; 
 int /*<<< orphan*/  ehca_alloc_mw ; 
 int /*<<< orphan*/  ehca_alloc_pd ; 
 int /*<<< orphan*/  ehca_alloc_ucontext ; 
 int /*<<< orphan*/  ehca_attach_mcast ; 
 int /*<<< orphan*/  ehca_bind_mw ; 
 int /*<<< orphan*/  ehca_create_ah ; 
 int /*<<< orphan*/  ehca_create_cq ; 
 int /*<<< orphan*/  ehca_create_qp ; 
 int /*<<< orphan*/  ehca_create_srq ; 
 int /*<<< orphan*/  ehca_dealloc_fmr ; 
 int /*<<< orphan*/  ehca_dealloc_mw ; 
 int /*<<< orphan*/  ehca_dealloc_pd ; 
 int /*<<< orphan*/  ehca_dealloc_ucontext ; 
 int /*<<< orphan*/  ehca_dereg_mr ; 
 int /*<<< orphan*/  ehca_destroy_ah ; 
 int /*<<< orphan*/  ehca_destroy_cq ; 
 int /*<<< orphan*/  ehca_destroy_qp ; 
 int /*<<< orphan*/  ehca_destroy_srq ; 
 int /*<<< orphan*/  ehca_detach_mcast ; 
 int /*<<< orphan*/  ehca_dma_mapping_ops ; 
 int /*<<< orphan*/  ehca_get_dma_mr ; 
 int /*<<< orphan*/  ehca_map_phys_fmr ; 
 int /*<<< orphan*/  ehca_mmap ; 
 int /*<<< orphan*/  ehca_modify_port ; 
 int /*<<< orphan*/  ehca_modify_qp ; 
 int /*<<< orphan*/  ehca_modify_srq ; 
 int /*<<< orphan*/  ehca_poll_cq ; 
 int /*<<< orphan*/  ehca_post_recv ; 
 int /*<<< orphan*/  ehca_post_send ; 
 int /*<<< orphan*/  ehca_post_srq_recv ; 
 int /*<<< orphan*/  ehca_process_mad ; 
 int /*<<< orphan*/  ehca_query_ah ; 
 int /*<<< orphan*/  ehca_query_device ; 
 int /*<<< orphan*/  ehca_query_gid ; 
 int /*<<< orphan*/  ehca_query_mr ; 
 int /*<<< orphan*/  ehca_query_pkey ; 
 int /*<<< orphan*/  ehca_query_port ; 
 int /*<<< orphan*/  ehca_query_qp ; 
 int /*<<< orphan*/  ehca_query_srq ; 
 int /*<<< orphan*/  ehca_reg_phys_mr ; 
 int /*<<< orphan*/  ehca_reg_user_mr ; 
 int /*<<< orphan*/  ehca_req_notify_cq ; 
 int /*<<< orphan*/  ehca_rereg_phys_mr ; 
 int /*<<< orphan*/  ehca_resize_cq ; 
 int /*<<< orphan*/  ehca_unmap_fmr ; 
 int init_node_guid (struct ehca_shca*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehca_init_device(struct ehca_shca *shca)
{
	int ret;

	ret = init_node_guid(shca);
	if (ret)
		return ret;

	strlcpy(shca->ib_device.name, "ehca%d", IB_DEVICE_NAME_MAX);
	shca->ib_device.owner               = THIS_MODULE;

	shca->ib_device.uverbs_abi_ver	    = 8;
	shca->ib_device.uverbs_cmd_mask	    =
		(1ull << IB_USER_VERBS_CMD_GET_CONTEXT)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_DEVICE)	|
		(1ull << IB_USER_VERBS_CMD_QUERY_PORT)		|
		(1ull << IB_USER_VERBS_CMD_ALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_DEALLOC_PD)		|
		(1ull << IB_USER_VERBS_CMD_REG_MR)		|
		(1ull << IB_USER_VERBS_CMD_DEREG_MR)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL)	|
		(1ull << IB_USER_VERBS_CMD_CREATE_CQ)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_CQ)		|
		(1ull << IB_USER_VERBS_CMD_CREATE_QP)		|
		(1ull << IB_USER_VERBS_CMD_MODIFY_QP)		|
		(1ull << IB_USER_VERBS_CMD_QUERY_QP)		|
		(1ull << IB_USER_VERBS_CMD_DESTROY_QP)		|
		(1ull << IB_USER_VERBS_CMD_ATTACH_MCAST)	|
		(1ull << IB_USER_VERBS_CMD_DETACH_MCAST);

	shca->ib_device.node_type           = RDMA_NODE_IB_CA;
	shca->ib_device.phys_port_cnt       = shca->num_ports;
	shca->ib_device.num_comp_vectors    = 1;
	shca->ib_device.dma_device          = &shca->ofdev->dev;
	shca->ib_device.query_device        = ehca_query_device;
	shca->ib_device.query_port          = ehca_query_port;
	shca->ib_device.query_gid           = ehca_query_gid;
	shca->ib_device.query_pkey          = ehca_query_pkey;
	/* shca->in_device.modify_device    = ehca_modify_device    */
	shca->ib_device.modify_port         = ehca_modify_port;
	shca->ib_device.alloc_ucontext      = ehca_alloc_ucontext;
	shca->ib_device.dealloc_ucontext    = ehca_dealloc_ucontext;
	shca->ib_device.alloc_pd            = ehca_alloc_pd;
	shca->ib_device.dealloc_pd          = ehca_dealloc_pd;
	shca->ib_device.create_ah	    = ehca_create_ah;
	/* shca->ib_device.modify_ah	    = ehca_modify_ah;	    */
	shca->ib_device.query_ah	    = ehca_query_ah;
	shca->ib_device.destroy_ah	    = ehca_destroy_ah;
	shca->ib_device.create_qp	    = ehca_create_qp;
	shca->ib_device.modify_qp	    = ehca_modify_qp;
	shca->ib_device.query_qp	    = ehca_query_qp;
	shca->ib_device.destroy_qp	    = ehca_destroy_qp;
	shca->ib_device.post_send	    = ehca_post_send;
	shca->ib_device.post_recv	    = ehca_post_recv;
	shca->ib_device.create_cq	    = ehca_create_cq;
	shca->ib_device.destroy_cq	    = ehca_destroy_cq;
	shca->ib_device.resize_cq	    = ehca_resize_cq;
	shca->ib_device.poll_cq		    = ehca_poll_cq;
	/* shca->ib_device.peek_cq	    = ehca_peek_cq;	    */
	shca->ib_device.req_notify_cq	    = ehca_req_notify_cq;
	/* shca->ib_device.req_ncomp_notif  = ehca_req_ncomp_notif; */
	shca->ib_device.get_dma_mr	    = ehca_get_dma_mr;
	shca->ib_device.reg_phys_mr	    = ehca_reg_phys_mr;
	shca->ib_device.reg_user_mr	    = ehca_reg_user_mr;
	shca->ib_device.query_mr	    = ehca_query_mr;
	shca->ib_device.dereg_mr	    = ehca_dereg_mr;
	shca->ib_device.rereg_phys_mr	    = ehca_rereg_phys_mr;
	shca->ib_device.alloc_mw	    = ehca_alloc_mw;
	shca->ib_device.bind_mw		    = ehca_bind_mw;
	shca->ib_device.dealloc_mw	    = ehca_dealloc_mw;
	shca->ib_device.alloc_fmr	    = ehca_alloc_fmr;
	shca->ib_device.map_phys_fmr	    = ehca_map_phys_fmr;
	shca->ib_device.unmap_fmr	    = ehca_unmap_fmr;
	shca->ib_device.dealloc_fmr	    = ehca_dealloc_fmr;
	shca->ib_device.attach_mcast	    = ehca_attach_mcast;
	shca->ib_device.detach_mcast	    = ehca_detach_mcast;
	shca->ib_device.process_mad	    = ehca_process_mad;
	shca->ib_device.mmap		    = ehca_mmap;
	shca->ib_device.dma_ops		    = &ehca_dma_mapping_ops;

	if (EHCA_BMASK_GET(HCA_CAP_SRQ, shca->hca_cap)) {
		shca->ib_device.uverbs_cmd_mask |=
			(1ull << IB_USER_VERBS_CMD_CREATE_SRQ) |
			(1ull << IB_USER_VERBS_CMD_MODIFY_SRQ) |
			(1ull << IB_USER_VERBS_CMD_QUERY_SRQ) |
			(1ull << IB_USER_VERBS_CMD_DESTROY_SRQ);

		shca->ib_device.create_srq          = ehca_create_srq;
		shca->ib_device.modify_srq          = ehca_modify_srq;
		shca->ib_device.query_srq           = ehca_query_srq;
		shca->ib_device.destroy_srq         = ehca_destroy_srq;
		shca->ib_device.post_srq_recv       = ehca_post_srq_recv;
	}

	return ret;
}