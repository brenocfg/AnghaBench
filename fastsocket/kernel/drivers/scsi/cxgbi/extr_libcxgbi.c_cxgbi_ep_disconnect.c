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
struct iscsi_endpoint {struct cxgbi_endpoint* dd_data; } ;
struct cxgbi_sock {scalar_t__ state; int /*<<< orphan*/  callback_lock; int /*<<< orphan*/ * user_data; int /*<<< orphan*/  flags; } ;
struct cxgbi_endpoint {struct cxgbi_sock* csk; struct cxgbi_conn* cconn; } ;
struct cxgbi_conn {int /*<<< orphan*/ * cep; scalar_t__ iconn; } ;

/* Variables and functions */
 scalar_t__ CTP_ESTABLISHED ; 
 int CXGBI_DBG_ISCSI ; 
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  cxgbi_sock_closed (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  iscsi_destroy_endpoint (struct iscsi_endpoint*) ; 
 int /*<<< orphan*/  iscsi_suspend_tx (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct iscsi_endpoint*,struct cxgbi_endpoint*,struct cxgbi_conn*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  need_active_close (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void cxgbi_ep_disconnect(struct iscsi_endpoint *ep)
{
	struct cxgbi_endpoint *cep = ep->dd_data;
	struct cxgbi_conn *cconn = cep->cconn;
	struct cxgbi_sock *csk = cep->csk;

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"ep 0x%p, cep 0x%p, cconn 0x%p, csk 0x%p,%u,0x%lx.\n",
		ep, cep, cconn, csk, csk->state, csk->flags);

	if (cconn && cconn->iconn) {
		iscsi_suspend_tx(cconn->iconn);
		write_lock_bh(&csk->callback_lock);
		cep->csk->user_data = NULL;
		cconn->cep = NULL;
		write_unlock_bh(&csk->callback_lock);
	}
	iscsi_destroy_endpoint(ep);

	if (likely(csk->state >= CTP_ESTABLISHED))
		need_active_close(csk);
	else
		cxgbi_sock_closed(csk);

	cxgbi_sock_put(csk);
}