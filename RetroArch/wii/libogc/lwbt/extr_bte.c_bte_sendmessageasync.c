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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pbuf {scalar_t__ payload; } ;
struct ctrl_req_t {int /*<<< orphan*/  (* sent ) (void*,struct bte_pcb*,u8) ;struct bte_pcb* pcb; struct pbuf* p; } ;
struct bte_pcb {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_CLSD ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int HIDP_DATA_RTYPE_OUPUT ; 
 int HIDP_TRANS_SETREPORT ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 scalar_t__ STATE_DISCONNECTED ; 
 scalar_t__ STATE_DISCONNECTING ; 
 int /*<<< orphan*/  __bte_send_request (struct ctrl_req_t*) ; 
 int /*<<< orphan*/  bte_ctrl_reqs ; 
 struct ctrl_req_t* btmemb_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct ctrl_req_t*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int /*<<< orphan*/ ) ; 

s32 bte_sendmessageasync(struct bte_pcb *pcb,void *message,u16 len,s32 (*sent)(void *arg,struct bte_pcb *pcb,u8 err))
{
	struct pbuf *p;
	struct ctrl_req_t *req;

	//printf("bte_sendmessageasync()\n");

	if(pcb==NULL || message==NULL || len==0) return ERR_VAL;
	if(pcb->state==STATE_DISCONNECTING || pcb->state==STATE_DISCONNECTED) return ERR_CLSD;

	if((req=btmemb_alloc(&bte_ctrl_reqs))==NULL) {
		ERROR("bte_sendmessageasync: Could not allocate memory for request\n");
		return ERR_MEM;
	}

	if((p=btpbuf_alloc(PBUF_RAW,(1 + len),PBUF_RAM))==NULL) {
		ERROR("bte_sendmessageasync: Could not allocate memory for pbuf\n");
		btmemb_free(&bte_ctrl_reqs,req);
		return ERR_MEM;
	}

	((u8*)p->payload)[0] = (HIDP_TRANS_SETREPORT|HIDP_DATA_RTYPE_OUPUT);
	memcpy(p->payload+1,message,len);

	req->p = p;
	req->pcb = pcb;
	req->sent = sent;
	return __bte_send_request(req);
}