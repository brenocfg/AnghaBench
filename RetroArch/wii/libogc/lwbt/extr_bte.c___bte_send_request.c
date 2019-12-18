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
struct ctrl_req_t {TYPE_1__* pcb; struct ctrl_req_t* next; int /*<<< orphan*/  state; int /*<<< orphan*/  err; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {struct ctrl_req_t* ctrl_req_tail; struct ctrl_req_t* ctrl_req_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  STATE_READY ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bte_send_pending_request (TYPE_1__*) ; 

__attribute__((used)) static s32 __bte_send_request(struct ctrl_req_t *req)
{
	s32 err;
	u32 level;

	req->next = NULL;
	req->err = ERR_VAL;
	req->state = STATE_READY;

	_CPU_ISR_Disable(level);
	if(req->pcb->ctrl_req_head==NULL) {
		req->pcb->ctrl_req_head = req->pcb->ctrl_req_tail = req;
		err = __bte_send_pending_request(req->pcb);
	} else {
		req->pcb->ctrl_req_tail->next = req;
		req->pcb->ctrl_req_tail = req;
		err = ERR_OK;
	}
	_CPU_ISR_Restore(level);

	return err;
}