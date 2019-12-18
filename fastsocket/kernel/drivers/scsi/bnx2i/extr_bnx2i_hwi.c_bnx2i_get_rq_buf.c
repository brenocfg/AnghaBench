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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2i_conn {TYPE_2__* ep; } ;
struct TYPE_3__ {scalar_t__ rq_cons_qe; scalar_t__ rq_last_qe; scalar_t__ rq_first_qe; scalar_t__ rq_cons_idx; int /*<<< orphan*/  rqe_left; } ;
struct TYPE_4__ {TYPE_1__ qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

void bnx2i_get_rq_buf(struct bnx2i_conn *bnx2i_conn, char *ptr, int len)
{
	if (!bnx2i_conn->ep->qp.rqe_left)
		return;

	bnx2i_conn->ep->qp.rqe_left--;
	memcpy(ptr, (u8 *) bnx2i_conn->ep->qp.rq_cons_qe, len);
	if (bnx2i_conn->ep->qp.rq_cons_qe == bnx2i_conn->ep->qp.rq_last_qe) {
		bnx2i_conn->ep->qp.rq_cons_qe = bnx2i_conn->ep->qp.rq_first_qe;
		bnx2i_conn->ep->qp.rq_cons_idx = 0;
	} else {
		bnx2i_conn->ep->qp.rq_cons_qe++;
		bnx2i_conn->ep->qp.rq_cons_idx++;
	}
}