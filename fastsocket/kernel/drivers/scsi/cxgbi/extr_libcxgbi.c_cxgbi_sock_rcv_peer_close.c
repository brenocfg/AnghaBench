#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cxgbi_sock {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_ABORT_RPL_PENDING ; 
#define  CTP_ABORTING 131 
#define  CTP_ACTIVE_CLOSE 130 
#define  CTP_CLOSE_WAIT_1 129 
 int /*<<< orphan*/  CTP_CLOSE_WAIT_2 ; 
#define  CTP_ESTABLISHED 128 
 int /*<<< orphan*/  CTP_PASSIVE_CLOSE ; 
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  cxgbi_inform_iscsi_conn_closing (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_closed (struct cxgbi_sock*) ; 
 scalar_t__ cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct cxgbi_sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cxgbi_sock_rcv_peer_close(struct cxgbi_sock *csk)
{
	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	if (cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING))
		goto done;

	switch (csk->state) {
	case CTP_ESTABLISHED:
		cxgbi_sock_set_state(csk, CTP_PASSIVE_CLOSE);
		break;
	case CTP_ACTIVE_CLOSE:
		cxgbi_sock_set_state(csk, CTP_CLOSE_WAIT_2);
		break;
	case CTP_CLOSE_WAIT_1:
		cxgbi_sock_closed(csk);
		break;
	case CTP_ABORTING:
		break;
	default:
		pr_err("csk 0x%p,%u,0x%lx,%u, bad state.\n",
			csk, csk->state, csk->flags, csk->tid);
	}
	cxgbi_inform_iscsi_conn_closing(csk);
done:
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
}