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
struct cxgbi_sock {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__* cdev; int /*<<< orphan*/  receive_queue; int /*<<< orphan*/  dst; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* csk_send_close_req ) (struct cxgbi_sock*) ;int /*<<< orphan*/  (* csk_send_abort_req ) (struct cxgbi_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_ACTIVE_CLOSE_NEEDED ; 
 int /*<<< orphan*/  CTP_ACTIVE_CLOSE ; 
 scalar_t__ CTP_ACTIVE_OPEN ; 
 int /*<<< orphan*/  CTP_CLOSE_WAIT_2 ; 
 scalar_t__ CTP_ESTABLISHED ; 
 scalar_t__ CTP_PASSIVE_CLOSE ; 
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  stub2 (struct cxgbi_sock*) ; 

__attribute__((used)) static void need_active_close(struct cxgbi_sock *csk)
{
	int data_lost;
	int close_req = 0;

	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	spin_lock_bh(&csk->lock);
	dst_confirm(csk->dst);
	data_lost = skb_queue_len(&csk->receive_queue);
	__skb_queue_purge(&csk->receive_queue);

	if (csk->state == CTP_ACTIVE_OPEN)
		cxgbi_sock_set_flag(csk, CTPF_ACTIVE_CLOSE_NEEDED);
	else if (csk->state == CTP_ESTABLISHED) {
		close_req = 1;
		cxgbi_sock_set_state(csk, CTP_ACTIVE_CLOSE);
	} else if (csk->state == CTP_PASSIVE_CLOSE) {
		close_req = 1;
		cxgbi_sock_set_state(csk, CTP_CLOSE_WAIT_2);
	}

	if (close_req) {
		if (data_lost)
			csk->cdev->csk_send_abort_req(csk);
		else
			csk->cdev->csk_send_close_req(csk);
	}

	spin_unlock_bh(&csk->lock);
}