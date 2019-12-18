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
struct ctrl_req_t {struct ctrl_req_t* next; int /*<<< orphan*/  (* sent ) (int /*<<< orphan*/ ,struct bte_pcb*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  state; int /*<<< orphan*/  err; } ;
struct bte_pcb {int /*<<< orphan*/ * ctrl_req_tail; struct ctrl_req_t* ctrl_req_head; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  cbarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CLSD ; 
 int /*<<< orphan*/  LWP_ThreadSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_DISCONNECTED ; 
 int /*<<< orphan*/  bte_ctrl_reqs ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct ctrl_req_t*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bte_pcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __bte_close_ctrl_queue(struct bte_pcb *pcb)
{
	struct ctrl_req_t *req;

	while(pcb->ctrl_req_head!=NULL) {
		req = pcb->ctrl_req_head;
		req->err = ERR_CLSD;
		req->state = STATE_DISCONNECTED;
		if(req->sent!=NULL) {
			req->sent(pcb->cbarg,pcb,ERR_CLSD);
			btmemb_free(&bte_ctrl_reqs,req);
		} else
			LWP_ThreadSignal(pcb->cmdq);

		pcb->ctrl_req_head = req->next;
	}
	pcb->ctrl_req_tail = NULL;
}