#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct nes_vnic {scalar_t__ local_ipaddr; struct nes_device* nesdev; } ;
struct TYPE_12__ {int /*<<< orphan*/  device; } ;
struct TYPE_13__ {int /*<<< orphan*/  qp_id; } ;
struct nes_qp {int active_conn; int private_data_len; TYPE_10__ ibqp; struct nes_cm_node* cm_node; TYPE_2__* nesqp_context; struct iw_cm_id* cm_id; TYPE_1__ hwqp; } ;
struct nes_device {TYPE_8__* pcidev; } ;
struct nes_cm_node {int apbvt_set; struct nes_qp* nesqp; } ;
struct nes_cm_info {int /*<<< orphan*/  conn_type; struct iw_cm_id* cm_id; void* rem_port; void* rem_addr; void* loc_port; void* loc_addr; } ;
struct TYPE_15__ {scalar_t__ s_addr; } ;
struct TYPE_19__ {int /*<<< orphan*/  sin_port; TYPE_3__ sin_addr; } ;
struct TYPE_16__ {scalar_t__ s_addr; } ;
struct TYPE_17__ {int /*<<< orphan*/  sin_port; TYPE_4__ sin_addr; } ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;TYPE_7__ local_addr; int /*<<< orphan*/  (* add_ref ) (struct iw_cm_id*) ;TYPE_5__ remote_addr; struct nes_qp* provider_data; int /*<<< orphan*/  device; } ;
struct iw_cm_conn_param {int private_data_len; scalar_t__ ord; scalar_t__ private_data; int /*<<< orphan*/  qpn; } ;
struct ib_qp {int dummy; } ;
struct TYPE_21__ {TYPE_6__* api; } ;
struct TYPE_20__ {int /*<<< orphan*/  devfn; } ;
struct TYPE_18__ {struct nes_cm_node* (* connect ) (TYPE_9__*,struct nes_vnic*,int,void*,struct nes_cm_info*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  ird_ord_sizes; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NES_CM_IWARP_CONN_TYPE ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  NES_MANAGE_APBVT_ADD ; 
 int /*<<< orphan*/  NES_MANAGE_APBVT_DEL ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_connects ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 TYPE_9__* g_cm_core ; 
 void* htonl (scalar_t__) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_add_ref (TYPE_10__*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 struct ib_qp* nes_get_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_manage_apbvt (struct nes_vnic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 struct nes_cm_node* stub2 (TYPE_9__*,struct nes_vnic*,int,void*,struct nes_cm_info*) ; 
 int /*<<< orphan*/  stub3 (struct iw_cm_id*) ; 
 struct nes_qp* to_nesqp (struct ib_qp*) ; 
 struct nes_vnic* to_nesvnic (int /*<<< orphan*/ ) ; 

int nes_connect(struct iw_cm_id *cm_id, struct iw_cm_conn_param *conn_param)
{
	struct ib_qp *ibqp;
	struct nes_qp *nesqp;
	struct nes_vnic *nesvnic;
	struct nes_device *nesdev;
	struct nes_cm_node *cm_node;
	struct nes_cm_info cm_info;
	int apbvt_set = 0;

	ibqp = nes_get_qp(cm_id->device, conn_param->qpn);
	if (!ibqp)
		return -EINVAL;
	nesqp = to_nesqp(ibqp);
	if (!nesqp)
		return -EINVAL;
	nesvnic = to_nesvnic(nesqp->ibqp.device);
	if (!nesvnic)
		return -EINVAL;
	nesdev = nesvnic->nesdev;
	if (!nesdev)
		return -EINVAL;

	if (!(cm_id->local_addr.sin_port) || !(cm_id->remote_addr.sin_port))
		return -EINVAL;

	nes_debug(NES_DBG_CM, "QP%u, current IP = 0x%08X, Destination IP = "
		  "0x%08X:0x%04X, local = 0x%08X:0x%04X.\n", nesqp->hwqp.qp_id,
		  ntohl(nesvnic->local_ipaddr),
		  ntohl(cm_id->remote_addr.sin_addr.s_addr),
		  ntohs(cm_id->remote_addr.sin_port),
		  ntohl(cm_id->local_addr.sin_addr.s_addr),
		  ntohs(cm_id->local_addr.sin_port));

	atomic_inc(&cm_connects);
	nesqp->active_conn = 1;

	/* cache the cm_id in the qp */
	nesqp->cm_id = cm_id;

	cm_id->provider_data = nesqp;

	nesqp->private_data_len = conn_param->private_data_len;
	nesqp->nesqp_context->ird_ord_sizes |= cpu_to_le32((u32)conn_param->ord);
	/* space for rdma0 read msg */
	if (conn_param->ord == 0)
		nesqp->nesqp_context->ird_ord_sizes |= cpu_to_le32(1);

	nes_debug(NES_DBG_CM, "requested ord = 0x%08X.\n", (u32)conn_param->ord);
	nes_debug(NES_DBG_CM, "mpa private data len =%u\n",
		  conn_param->private_data_len);

	if (cm_id->local_addr.sin_addr.s_addr !=
	    cm_id->remote_addr.sin_addr.s_addr) {
		nes_manage_apbvt(nesvnic, ntohs(cm_id->local_addr.sin_port),
				 PCI_FUNC(nesdev->pcidev->devfn), NES_MANAGE_APBVT_ADD);
		apbvt_set = 1;
	}

	/* set up the connection params for the node */
	cm_info.loc_addr = htonl(cm_id->local_addr.sin_addr.s_addr);
	cm_info.loc_port = htons(cm_id->local_addr.sin_port);
	cm_info.rem_addr = htonl(cm_id->remote_addr.sin_addr.s_addr);
	cm_info.rem_port = htons(cm_id->remote_addr.sin_port);
	cm_info.cm_id = cm_id;
	cm_info.conn_type = NES_CM_IWARP_CONN_TYPE;

	cm_id->add_ref(cm_id);

	/* create a connect CM node connection */
	cm_node = g_cm_core->api->connect(g_cm_core, nesvnic,
					  conn_param->private_data_len, (void *)conn_param->private_data,
					  &cm_info);
	if (!cm_node) {
		if (apbvt_set)
			nes_manage_apbvt(nesvnic, ntohs(cm_id->local_addr.sin_port),
					 PCI_FUNC(nesdev->pcidev->devfn),
					 NES_MANAGE_APBVT_DEL);

		cm_id->rem_ref(cm_id);
		return -ENOMEM;
	}

	cm_node->apbvt_set = apbvt_set;
	nesqp->cm_node = cm_node;
	cm_node->nesqp = nesqp;
	nes_add_ref(&nesqp->ibqp);

	return 0;
}