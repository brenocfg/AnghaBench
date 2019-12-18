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
typedef  int /*<<< orphan*/  u64 ;
struct iscsi_tcp_conn {struct cxgbi_conn* dd_data; } ;
struct iscsi_endpoint {struct cxgbi_endpoint* dd_data; } ;
struct iscsi_conn {TYPE_2__* session; struct iscsi_tcp_conn* dd_data; } ;
struct iscsi_cls_session {int dummy; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct cxgbi_sock {int /*<<< orphan*/  callback_lock; struct iscsi_conn* user_data; int /*<<< orphan*/  tid; TYPE_1__* cdev; } ;
struct cxgbi_endpoint {struct cxgbi_conn* cconn; int /*<<< orphan*/  chba; struct cxgbi_sock* csk; } ;
struct cxgbi_conn {struct cxgbi_endpoint* cep; int /*<<< orphan*/  chba; scalar_t__ task_idx_bits; } ;
struct TYPE_4__ {scalar_t__ cmds_max; } ;
struct TYPE_3__ {int (* csk_ddp_setup_pgidx ) (struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CXGBI_DBG_ISCSI ; 
 int EINVAL ; 
 scalar_t__ __ilog2_u32 (scalar_t__) ; 
 int /*<<< orphan*/  cxgbi_conn_max_recv_dlength (struct iscsi_conn*) ; 
 int /*<<< orphan*/  cxgbi_conn_max_xmit_dlength (struct iscsi_conn*) ; 
 int iscsi_conn_bind (struct iscsi_cls_session*,struct iscsi_cls_conn*,int) ; 
 struct iscsi_endpoint* iscsi_lookup_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_tcp_hdr_recv_prep (struct iscsi_tcp_conn*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct iscsi_cls_session*,struct iscsi_cls_conn*,struct iscsi_endpoint*,struct cxgbi_conn*,struct cxgbi_sock*) ; 
 int /*<<< orphan*/  page_idx ; 
 int stub1 (struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int cxgbi_bind_conn(struct iscsi_cls_session *cls_session,
				struct iscsi_cls_conn *cls_conn,
				u64 transport_eph, int is_leading)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct cxgbi_conn *cconn = tcp_conn->dd_data;
	struct iscsi_endpoint *ep;
	struct cxgbi_endpoint *cep;
	struct cxgbi_sock *csk;
	int err;

	ep = iscsi_lookup_endpoint(transport_eph);
	if (!ep)
		return -EINVAL;

	/*  setup ddp pagesize */
	cep = ep->dd_data;
	csk = cep->csk;
	err = csk->cdev->csk_ddp_setup_pgidx(csk, csk->tid, page_idx, 0);
	if (err < 0)
		return err;

	err = iscsi_conn_bind(cls_session, cls_conn, is_leading);
	if (err)
		return -EINVAL;

	/*  calculate the tag idx bits needed for this conn based on cmds_max */
	cconn->task_idx_bits = (__ilog2_u32(conn->session->cmds_max - 1)) + 1;

	write_lock_bh(&csk->callback_lock);
	csk->user_data = conn;
	cconn->chba = cep->chba;
	cconn->cep = cep;
	cep->cconn = cconn;
	write_unlock_bh(&csk->callback_lock);

	cxgbi_conn_max_xmit_dlength(conn);
	cxgbi_conn_max_recv_dlength(conn);

	log_debug(1 << CXGBI_DBG_ISCSI,
		"cls 0x%p,0x%p, ep 0x%p, cconn 0x%p, csk 0x%p.\n",
		cls_session, cls_conn, ep, cconn, csk);
	/*  init recv engine */
	iscsi_tcp_hdr_recv_prep(tcp_conn);

	return 0;
}