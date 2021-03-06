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
struct iser_conn {int /*<<< orphan*/  post_recv_buf_count; int /*<<< orphan*/  qp; scalar_t__ login_resp_buf; TYPE_2__* device; int /*<<< orphan*/  login_resp_dma; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct ib_recv_wr {unsigned long wr_id; int num_sge; int /*<<< orphan*/ * next; struct ib_sge* sg_list; } ;
struct TYPE_4__ {TYPE_1__* mr; } ;
struct TYPE_3__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_RX_LOGIN_SIZE ; 
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,struct ib_recv_wr**) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 

int iser_post_recvl(struct iser_conn *ib_conn)
{
	struct ib_recv_wr rx_wr, *rx_wr_failed;
	struct ib_sge	  sge;
	int ib_ret;

	sge.addr   = ib_conn->login_resp_dma;
	sge.length = ISER_RX_LOGIN_SIZE;
	sge.lkey   = ib_conn->device->mr->lkey;

	rx_wr.wr_id   = (unsigned long)ib_conn->login_resp_buf;
	rx_wr.sg_list = &sge;
	rx_wr.num_sge = 1;
	rx_wr.next    = NULL;

	ib_conn->post_recv_buf_count++;
	ib_ret	= ib_post_recv(ib_conn->qp, &rx_wr, &rx_wr_failed);
	if (ib_ret) {
		iser_err("ib_post_recv failed ret=%d\n", ib_ret);
		ib_conn->post_recv_buf_count--;
	}
	return ib_ret;
}