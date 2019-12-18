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
struct ctrl_req_t {int /*<<< orphan*/  (* sent ) (int /*<<< orphan*/ ,struct bte_pcb*,scalar_t__) ;int /*<<< orphan*/  state; scalar_t__ err; struct ctrl_req_t* next; int /*<<< orphan*/  p; } ;
struct bte_pcb {scalar_t__ state; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  cbarg; struct ctrl_req_t* ctrl_req_head; int /*<<< orphan*/  ctl_pcb; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ ERR_CLSD ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWP_ThreadSignal (int /*<<< orphan*/ ) ; 
 scalar_t__ STATE_DISCONNECTED ; 
 scalar_t__ STATE_DISCONNECTING ; 
 int /*<<< orphan*/  STATE_FAILED ; 
 int /*<<< orphan*/  STATE_SENDING ; 
 int /*<<< orphan*/  bte_ctrl_reqs ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct ctrl_req_t*) ; 
 int /*<<< orphan*/  btpbuf_free (int /*<<< orphan*/ ) ; 
 scalar_t__ l2ca_datawrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bte_pcb*,scalar_t__) ; 

__attribute__((used)) static s32 __bte_send_pending_request(struct bte_pcb *pcb)
{
	s32 err;
	struct ctrl_req_t *req;

	if(pcb->ctrl_req_head==NULL) return ERR_OK;
	if(pcb->state==STATE_DISCONNECTING || pcb->state==STATE_DISCONNECTED) return ERR_CLSD;

	req = pcb->ctrl_req_head;
	req->state = STATE_SENDING;

	err = l2ca_datawrite(pcb->ctl_pcb,req->p);
	btpbuf_free(req->p);

	if(err!=ERR_OK) {
		pcb->ctrl_req_head = req->next;

		req->err = err;
		req->state = STATE_FAILED;
		if(req->sent) {
			req->sent(pcb->cbarg,pcb,err);
			btmemb_free(&bte_ctrl_reqs,req);
		} else
			LWP_ThreadSignal(pcb->cmdq);
	}

	return err;
}