#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {unsigned long long uverbs_cmd_mask; int phys_port_cnt; int num_comp_vectors; TYPE_3__* iwcm; int /*<<< orphan*/  post_recv; int /*<<< orphan*/  post_send; int /*<<< orphan*/  req_notify_cq; int /*<<< orphan*/  process_mad; int /*<<< orphan*/  detach_mcast; int /*<<< orphan*/  attach_mcast; int /*<<< orphan*/  free_fast_reg_page_list; int /*<<< orphan*/  alloc_fast_reg_page_list; int /*<<< orphan*/  alloc_fast_reg_mr; int /*<<< orphan*/  bind_mw; int /*<<< orphan*/  dealloc_mw; int /*<<< orphan*/  alloc_mw; int /*<<< orphan*/  dereg_mr; int /*<<< orphan*/  reg_user_mr; int /*<<< orphan*/  reg_phys_mr; int /*<<< orphan*/  get_dma_mr; int /*<<< orphan*/  poll_cq; int /*<<< orphan*/  destroy_cq; int /*<<< orphan*/  create_cq; int /*<<< orphan*/  destroy_qp; int /*<<< orphan*/  query_qp; int /*<<< orphan*/  modify_qp; int /*<<< orphan*/  create_qp; int /*<<< orphan*/  destroy_ah; int /*<<< orphan*/  create_ah; int /*<<< orphan*/  dealloc_pd; int /*<<< orphan*/  alloc_pd; int /*<<< orphan*/  mmap; int /*<<< orphan*/  dealloc_ucontext; int /*<<< orphan*/  alloc_ucontext; int /*<<< orphan*/  query_gid; int /*<<< orphan*/  query_pkey; int /*<<< orphan*/  query_port; int /*<<< orphan*/  query_device; TYPE_1__ dev; int /*<<< orphan*/ * dma_device; int /*<<< orphan*/  node_guid; int /*<<< orphan*/  node_type; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct nes_ib_device {TYPE_4__ ibdev; } ;
struct nes_device {TYPE_2__* pcidev; } ;
struct TYPE_7__ {int /*<<< orphan*/  destroy_listen; int /*<<< orphan*/  create_listen; int /*<<< orphan*/  reject; int /*<<< orphan*/  accept; int /*<<< orphan*/  connect; int /*<<< orphan*/  get_qp; int /*<<< orphan*/  rem_ref; int /*<<< orphan*/  add_ref; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_DEVICE_NAME_MAX ; 
 unsigned long long IB_USER_VERBS_CMD_ALLOC_MW ; 
 unsigned long long IB_USER_VERBS_CMD_ALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_BIND_MW ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_AH ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_CREATE_QP ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_MW ; 
 unsigned long long IB_USER_VERBS_CMD_DEALLOC_PD ; 
 unsigned long long IB_USER_VERBS_CMD_DEREG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_AH ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_DESTROY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_GET_CONTEXT ; 
 unsigned long long IB_USER_VERBS_CMD_MODIFY_QP ; 
 unsigned long long IB_USER_VERBS_CMD_POLL_CQ ; 
 unsigned long long IB_USER_VERBS_CMD_POST_RECV ; 
 unsigned long long IB_USER_VERBS_CMD_POST_SEND ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_DEVICE ; 
 unsigned long long IB_USER_VERBS_CMD_QUERY_PORT ; 
 unsigned long long IB_USER_VERBS_CMD_REG_MR ; 
 unsigned long long IB_USER_VERBS_CMD_REQ_NOTIFY_CQ ; 
 int /*<<< orphan*/  RDMA_NODE_RNIC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ ib_alloc_device (int) ; 
 int /*<<< orphan*/  ib_dealloc_device (TYPE_4__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nes_accept ; 
 int /*<<< orphan*/  nes_add_ref ; 
 int /*<<< orphan*/  nes_alloc_fast_reg_mr ; 
 int /*<<< orphan*/  nes_alloc_fast_reg_page_list ; 
 int /*<<< orphan*/  nes_alloc_mw ; 
 int /*<<< orphan*/  nes_alloc_pd ; 
 int /*<<< orphan*/  nes_alloc_ucontext ; 
 int /*<<< orphan*/  nes_bind_mw ; 
 int /*<<< orphan*/  nes_connect ; 
 int /*<<< orphan*/  nes_create_ah ; 
 int /*<<< orphan*/  nes_create_cq ; 
 int /*<<< orphan*/  nes_create_listen ; 
 int /*<<< orphan*/  nes_create_qp ; 
 int /*<<< orphan*/  nes_dealloc_mw ; 
 int /*<<< orphan*/  nes_dealloc_pd ; 
 int /*<<< orphan*/  nes_dealloc_ucontext ; 
 int /*<<< orphan*/  nes_dereg_mr ; 
 int /*<<< orphan*/  nes_destroy_ah ; 
 int /*<<< orphan*/  nes_destroy_cq ; 
 int /*<<< orphan*/  nes_destroy_listen ; 
 int /*<<< orphan*/  nes_destroy_qp ; 
 int /*<<< orphan*/  nes_free_fast_reg_page_list ; 
 int /*<<< orphan*/  nes_get_dma_mr ; 
 int /*<<< orphan*/  nes_get_qp ; 
 int /*<<< orphan*/  nes_mmap ; 
 int /*<<< orphan*/  nes_modify_qp ; 
 int /*<<< orphan*/  nes_multicast_attach ; 
 int /*<<< orphan*/  nes_multicast_detach ; 
 int /*<<< orphan*/  nes_poll_cq ; 
 int /*<<< orphan*/  nes_post_recv ; 
 int /*<<< orphan*/  nes_post_send ; 
 int /*<<< orphan*/  nes_process_mad ; 
 int /*<<< orphan*/  nes_query_device ; 
 int /*<<< orphan*/  nes_query_gid ; 
 int /*<<< orphan*/  nes_query_pkey ; 
 int /*<<< orphan*/  nes_query_port ; 
 int /*<<< orphan*/  nes_query_qp ; 
 int /*<<< orphan*/  nes_reg_phys_mr ; 
 int /*<<< orphan*/  nes_reg_user_mr ; 
 int /*<<< orphan*/  nes_reject ; 
 int /*<<< orphan*/  nes_rem_ref ; 
 int /*<<< orphan*/  nes_req_notify_cq ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct nes_ib_device *nes_init_ofa_device(struct net_device *netdev)
{
	struct nes_ib_device *nesibdev;
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;

	nesibdev = (struct nes_ib_device *)ib_alloc_device(sizeof(struct nes_ib_device));
	if (nesibdev == NULL) {
		return NULL;
	}
	strlcpy(nesibdev->ibdev.name, "nes%d", IB_DEVICE_NAME_MAX);
	nesibdev->ibdev.owner = THIS_MODULE;

	nesibdev->ibdev.node_type = RDMA_NODE_RNIC;
	memset(&nesibdev->ibdev.node_guid, 0, sizeof(nesibdev->ibdev.node_guid));
	memcpy(&nesibdev->ibdev.node_guid, netdev->dev_addr, 6);

	nesibdev->ibdev.uverbs_cmd_mask =
			(1ull << IB_USER_VERBS_CMD_GET_CONTEXT) |
			(1ull << IB_USER_VERBS_CMD_QUERY_DEVICE) |
			(1ull << IB_USER_VERBS_CMD_QUERY_PORT) |
			(1ull << IB_USER_VERBS_CMD_ALLOC_PD) |
			(1ull << IB_USER_VERBS_CMD_DEALLOC_PD) |
			(1ull << IB_USER_VERBS_CMD_REG_MR) |
			(1ull << IB_USER_VERBS_CMD_DEREG_MR) |
			(1ull << IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL) |
			(1ull << IB_USER_VERBS_CMD_CREATE_CQ) |
			(1ull << IB_USER_VERBS_CMD_DESTROY_CQ) |
			(1ull << IB_USER_VERBS_CMD_CREATE_AH) |
			(1ull << IB_USER_VERBS_CMD_DESTROY_AH) |
			(1ull << IB_USER_VERBS_CMD_REQ_NOTIFY_CQ) |
			(1ull << IB_USER_VERBS_CMD_CREATE_QP) |
			(1ull << IB_USER_VERBS_CMD_MODIFY_QP) |
			(1ull << IB_USER_VERBS_CMD_POLL_CQ) |
			(1ull << IB_USER_VERBS_CMD_DESTROY_QP) |
			(1ull << IB_USER_VERBS_CMD_ALLOC_MW) |
			(1ull << IB_USER_VERBS_CMD_BIND_MW) |
			(1ull << IB_USER_VERBS_CMD_DEALLOC_MW) |
			(1ull << IB_USER_VERBS_CMD_POST_RECV) |
			(1ull << IB_USER_VERBS_CMD_POST_SEND);

	nesibdev->ibdev.phys_port_cnt = 1;
	nesibdev->ibdev.num_comp_vectors = 1;
	nesibdev->ibdev.dma_device = &nesdev->pcidev->dev;
	nesibdev->ibdev.dev.parent = &nesdev->pcidev->dev;
	nesibdev->ibdev.query_device = nes_query_device;
	nesibdev->ibdev.query_port = nes_query_port;
	nesibdev->ibdev.query_pkey = nes_query_pkey;
	nesibdev->ibdev.query_gid = nes_query_gid;
	nesibdev->ibdev.alloc_ucontext = nes_alloc_ucontext;
	nesibdev->ibdev.dealloc_ucontext = nes_dealloc_ucontext;
	nesibdev->ibdev.mmap = nes_mmap;
	nesibdev->ibdev.alloc_pd = nes_alloc_pd;
	nesibdev->ibdev.dealloc_pd = nes_dealloc_pd;
	nesibdev->ibdev.create_ah = nes_create_ah;
	nesibdev->ibdev.destroy_ah = nes_destroy_ah;
	nesibdev->ibdev.create_qp = nes_create_qp;
	nesibdev->ibdev.modify_qp = nes_modify_qp;
	nesibdev->ibdev.query_qp = nes_query_qp;
	nesibdev->ibdev.destroy_qp = nes_destroy_qp;
	nesibdev->ibdev.create_cq = nes_create_cq;
	nesibdev->ibdev.destroy_cq = nes_destroy_cq;
	nesibdev->ibdev.poll_cq = nes_poll_cq;
	nesibdev->ibdev.get_dma_mr = nes_get_dma_mr;
	nesibdev->ibdev.reg_phys_mr = nes_reg_phys_mr;
	nesibdev->ibdev.reg_user_mr = nes_reg_user_mr;
	nesibdev->ibdev.dereg_mr = nes_dereg_mr;
	nesibdev->ibdev.alloc_mw = nes_alloc_mw;
	nesibdev->ibdev.dealloc_mw = nes_dealloc_mw;
	nesibdev->ibdev.bind_mw = nes_bind_mw;

	nesibdev->ibdev.alloc_fast_reg_mr = nes_alloc_fast_reg_mr;
	nesibdev->ibdev.alloc_fast_reg_page_list = nes_alloc_fast_reg_page_list;
	nesibdev->ibdev.free_fast_reg_page_list = nes_free_fast_reg_page_list;

	nesibdev->ibdev.attach_mcast = nes_multicast_attach;
	nesibdev->ibdev.detach_mcast = nes_multicast_detach;
	nesibdev->ibdev.process_mad = nes_process_mad;

	nesibdev->ibdev.req_notify_cq = nes_req_notify_cq;
	nesibdev->ibdev.post_send = nes_post_send;
	nesibdev->ibdev.post_recv = nes_post_recv;

	nesibdev->ibdev.iwcm = kzalloc(sizeof(*nesibdev->ibdev.iwcm), GFP_KERNEL);
	if (nesibdev->ibdev.iwcm == NULL) {
		ib_dealloc_device(&nesibdev->ibdev);
		return NULL;
	}
	nesibdev->ibdev.iwcm->add_ref = nes_add_ref;
	nesibdev->ibdev.iwcm->rem_ref = nes_rem_ref;
	nesibdev->ibdev.iwcm->get_qp = nes_get_qp;
	nesibdev->ibdev.iwcm->connect = nes_connect;
	nesibdev->ibdev.iwcm->accept = nes_accept;
	nesibdev->ibdev.iwcm->reject = nes_reject;
	nesibdev->ibdev.iwcm->create_listen = nes_create_listen;
	nesibdev->ibdev.iwcm->destroy_listen = nes_destroy_listen;

	return nesibdev;
}