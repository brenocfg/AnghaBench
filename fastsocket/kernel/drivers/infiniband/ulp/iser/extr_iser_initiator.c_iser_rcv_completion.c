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
typedef  scalar_t__ u64 ;
struct iscsi_hdr {int /*<<< orphan*/  itt; int /*<<< orphan*/  opcode; } ;
struct iser_rx_desc {scalar_t__ dma_addr; int /*<<< orphan*/  data; struct iscsi_hdr iscsi_header; } ;
struct iser_conn {char* login_resp_buf; scalar_t__ login_resp_dma; int post_recv_buf_count; TYPE_1__* device; struct iscsi_iser_conn* iser_conn; } ;
struct iscsi_iser_conn {TYPE_2__* ib_conn; int /*<<< orphan*/  iscsi_conn; } ;
struct TYPE_4__ {int /*<<< orphan*/  post_recv_buf_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  ib_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned long ISER_HEADERS_LEN ; 
 scalar_t__ ISER_MIN_POSTED_RX ; 
 scalar_t__ ISER_QP_MAX_RECV_DTOS ; 
 int ISER_RX_LOGIN_SIZE ; 
 int ISER_RX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_iser_recv (int /*<<< orphan*/ ,struct iscsi_hdr*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iser_err (char*,int,int) ; 
 int iser_post_recvm (struct iser_conn*,int) ; 
 int min (scalar_t__,scalar_t__) ; 

void iser_rcv_completion(struct iser_rx_desc *rx_desc,
			 unsigned long rx_xfer_len,
			 struct iser_conn *ib_conn)
{
	struct iscsi_iser_conn *conn = ib_conn->iser_conn;
	struct iscsi_hdr *hdr;
	u64 rx_dma;
	int rx_buflen, outstanding, count, err;

	/* differentiate between login to all other PDUs */
	if ((char *)rx_desc == ib_conn->login_resp_buf) {
		rx_dma = ib_conn->login_resp_dma;
		rx_buflen = ISER_RX_LOGIN_SIZE;
	} else {
		rx_dma = rx_desc->dma_addr;
		rx_buflen = ISER_RX_PAYLOAD_SIZE;
	}

	ib_dma_sync_single_for_cpu(ib_conn->device->ib_device, rx_dma,
			rx_buflen, DMA_FROM_DEVICE);

	hdr = &rx_desc->iscsi_header;

	iser_dbg("op 0x%x itt 0x%x dlen %d\n", hdr->opcode,
			hdr->itt, (int)(rx_xfer_len - ISER_HEADERS_LEN));

	iscsi_iser_recv(conn->iscsi_conn, hdr,
		rx_desc->data, rx_xfer_len - ISER_HEADERS_LEN);

	ib_dma_sync_single_for_device(ib_conn->device->ib_device, rx_dma,
			rx_buflen, DMA_FROM_DEVICE);

	/* decrementing conn->post_recv_buf_count only --after-- freeing the   *
	 * task eliminates the need to worry on tasks which are completed in   *
	 * parallel to the execution of iser_conn_term. So the code that waits *
	 * for the posted rx bufs refcount to become zero handles everything   */
	conn->ib_conn->post_recv_buf_count--;

	if (rx_dma == ib_conn->login_resp_dma)
		return;

	outstanding = ib_conn->post_recv_buf_count;
	if (outstanding + ISER_MIN_POSTED_RX <= ISER_QP_MAX_RECV_DTOS) {
		count = min(ISER_QP_MAX_RECV_DTOS - outstanding,
						ISER_MIN_POSTED_RX);
		err = iser_post_recvm(ib_conn, count);
		if (err)
			iser_err("posting %d rx bufs err %d\n", count, err);
	}
}