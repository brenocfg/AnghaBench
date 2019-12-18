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
typedef  int /*<<< orphan*/  u32 ;
struct p9_trans_rdma {int /*<<< orphan*/  state; TYPE_1__* cm_id; } ;
struct p9_req_t {int /*<<< orphan*/  status; int /*<<< orphan*/  rc; } ;
struct p9_rdma_context {int /*<<< orphan*/  rc; int /*<<< orphan*/  busa; } ;
struct p9_client {int /*<<< orphan*/  status; int /*<<< orphan*/  msize; } ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  Disconnected ; 
 int IB_WC_SUCCESS ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct p9_req_t*,int,int) ; 
 int /*<<< orphan*/  P9_RDMA_FLUSHING ; 
 int /*<<< orphan*/  REQ_STATUS_RCVD ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_client_cb (struct p9_client*,struct p9_req_t*) ; 
 int p9_parse_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct p9_req_t* p9_tag_lookup (struct p9_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_recv(struct p9_client *client, struct p9_trans_rdma *rdma,
	    struct p9_rdma_context *c, enum ib_wc_status status, u32 byte_len)
{
	struct p9_req_t *req;
	int err = 0;
	int16_t tag;

	req = NULL;
	ib_dma_unmap_single(rdma->cm_id->device, c->busa, client->msize,
							 DMA_FROM_DEVICE);

	if (status != IB_WC_SUCCESS)
		goto err_out;

	err = p9_parse_header(c->rc, NULL, NULL, &tag, 1);
	if (err)
		goto err_out;

	req = p9_tag_lookup(client, tag);
	if (!req)
		goto err_out;

	req->rc = c->rc;
	req->status = REQ_STATUS_RCVD;
	p9_client_cb(client, req);

	return;

 err_out:
	P9_DPRINTK(P9_DEBUG_ERROR, "req %p err %d status %d\n",
		   req, err, status);
	rdma->state = P9_RDMA_FLUSHING;
	client->status = Disconnected;
	return;
}