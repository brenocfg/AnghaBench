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
typedef  int /*<<< orphan*/  u64 ;
struct iser_page_vec {int dummy; } ;
struct iser_device {int cqs_used; scalar_t__* cq_active_qps; int /*<<< orphan*/  pd; int /*<<< orphan*/ * rx_cq; int /*<<< orphan*/ * tx_cq; int /*<<< orphan*/  ib_device; } ;
struct iser_conn {int login_buf; int login_req_buf; int login_resp_buf; TYPE_3__* cma_id; int /*<<< orphan*/ * fmr_pool; int /*<<< orphan*/  qp; TYPE_1__* page_vec; void* login_resp_dma; void* login_req_dma; struct iser_device* device; } ;
struct TYPE_6__ {int max_send_sge; int max_recv_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; TYPE_2__ cap; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; void* qp_context; int /*<<< orphan*/  event_handler; } ;
struct ib_fmr_pool_param {int max_pages_per_fmr; int pool_size; int dirty_watermark; int access; int /*<<< orphan*/ * flush_function; scalar_t__ cache; int /*<<< orphan*/  page_shift; } ;
struct TYPE_8__ {int /*<<< orphan*/  connlist_mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  qp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 int /*<<< orphan*/  IB_SIGNAL_REQ_WR ; 
 int ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int ISCSI_DEF_XMIT_CMDS_MAX ; 
 int ISCSI_ISER_SG_TABLESIZE ; 
 int /*<<< orphan*/  ISER_QP_MAX_RECV_DTOS ; 
 int /*<<< orphan*/  ISER_QP_MAX_REQ_DTOS ; 
 int ISER_RX_LOGIN_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHIFT_4K ; 
 int /*<<< orphan*/ * ib_create_fmr_pool (int /*<<< orphan*/ ,struct ib_fmr_pool_param*) ; 
 void* ib_dma_map_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int ib_dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 TYPE_4__ ig ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 
 int /*<<< orphan*/  iser_info (char*,...) ; 
 int /*<<< orphan*/  iser_qp_event_callback ; 
 int /*<<< orphan*/  iser_warn (char*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rdma_create_qp (TYPE_3__*,int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 

__attribute__((used)) static int iser_create_ib_conn_res(struct iser_conn *ib_conn)
{
	struct iser_device	*device;
	struct ib_qp_init_attr	init_attr;
	int			req_err, resp_err, ret = -ENOMEM;
	struct ib_fmr_pool_param params;
	int index, min_index = 0;

	BUG_ON(ib_conn->device == NULL);

	device = ib_conn->device;

	ib_conn->login_buf = kmalloc(ISCSI_DEF_MAX_RECV_SEG_LEN +
					ISER_RX_LOGIN_SIZE, GFP_KERNEL);
	if (!ib_conn->login_buf)
		goto out_err;

	ib_conn->login_req_buf  = ib_conn->login_buf;
	ib_conn->login_resp_buf = ib_conn->login_buf + ISCSI_DEF_MAX_RECV_SEG_LEN;

	ib_conn->login_req_dma = ib_dma_map_single(ib_conn->device->ib_device,
				(void *)ib_conn->login_req_buf,
				ISCSI_DEF_MAX_RECV_SEG_LEN, DMA_TO_DEVICE);

	ib_conn->login_resp_dma = ib_dma_map_single(ib_conn->device->ib_device,
				(void *)ib_conn->login_resp_buf,
				ISER_RX_LOGIN_SIZE, DMA_FROM_DEVICE);

	req_err  = ib_dma_mapping_error(device->ib_device, ib_conn->login_req_dma);
	resp_err = ib_dma_mapping_error(device->ib_device, ib_conn->login_resp_dma);

	if (req_err || resp_err) {
		if (req_err)
			ib_conn->login_req_dma = 0;
		if (resp_err)
			ib_conn->login_resp_dma = 0;
		goto out_err;
	}

	ib_conn->page_vec = kmalloc(sizeof(struct iser_page_vec) +
				    (sizeof(u64) * (ISCSI_ISER_SG_TABLESIZE +1)),
				    GFP_KERNEL);
	if (!ib_conn->page_vec) {
		goto out_err;
	}
	ib_conn->page_vec->pages = (u64 *) (ib_conn->page_vec + 1);

	params.page_shift        = SHIFT_4K;
	/* when the first/last SG element are not start/end *
	 * page aligned, the map whould be of N+1 pages     */
	params.max_pages_per_fmr = ISCSI_ISER_SG_TABLESIZE + 1;
	/* make the pool size twice the max number of SCSI commands *
	 * the ML is expected to queue, watermark for unmap at 50%  */
	params.pool_size	 = ISCSI_DEF_XMIT_CMDS_MAX * 2;
	params.dirty_watermark	 = ISCSI_DEF_XMIT_CMDS_MAX;
	params.cache		 = 0;
	params.flush_function	 = NULL;
	params.access		 = (IB_ACCESS_LOCAL_WRITE  |
				    IB_ACCESS_REMOTE_WRITE |
				    IB_ACCESS_REMOTE_READ);

	ib_conn->fmr_pool = ib_create_fmr_pool(device->pd, &params);
	ret = PTR_ERR(ib_conn->fmr_pool);
	if (IS_ERR(ib_conn->fmr_pool) && ret != -ENOSYS) {
		ib_conn->fmr_pool = NULL;
		goto out_err;
	} else if (ret == -ENOSYS) {
		ib_conn->fmr_pool = NULL;
		iser_warn("FMRs are not supported, using unaligned mode\n");
		ret = 0;
	}

	memset(&init_attr, 0, sizeof init_attr);

	mutex_lock(&ig.connlist_mutex);
	/* select the CQ with the minimal number of usages */
	for (index = 0; index < device->cqs_used; index++)
		if (device->cq_active_qps[index] <
		    device->cq_active_qps[min_index])
			min_index = index;
	device->cq_active_qps[min_index]++;
	mutex_unlock(&ig.connlist_mutex);
	iser_info("cq index %d used for ib_conn %p\n", min_index, ib_conn);

	init_attr.event_handler = iser_qp_event_callback;
	init_attr.qp_context	= (void *)ib_conn;
	init_attr.send_cq	= device->tx_cq[min_index];
	init_attr.recv_cq	= device->rx_cq[min_index];
	init_attr.cap.max_send_wr  = ISER_QP_MAX_REQ_DTOS;
	init_attr.cap.max_recv_wr  = ISER_QP_MAX_RECV_DTOS;
	init_attr.cap.max_send_sge = 2;
	init_attr.cap.max_recv_sge = 1;
	init_attr.sq_sig_type	= IB_SIGNAL_REQ_WR;
	init_attr.qp_type	= IB_QPT_RC;

	ret = rdma_create_qp(ib_conn->cma_id, device->pd, &init_attr);
	if (ret)
		goto out_err;

	ib_conn->qp = ib_conn->cma_id->qp;
	iser_info("setting conn %p cma_id %p: fmr_pool %p qp %p\n",
		  ib_conn, ib_conn->cma_id,
		  ib_conn->fmr_pool, ib_conn->cma_id->qp);
	return ret;

out_err:
	iser_err("unable to alloc mem or create resource, err %d\n", ret);
	return ret;
}