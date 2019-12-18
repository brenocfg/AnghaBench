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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {scalar_t__ payload; } ;
struct l2cap_pcb {int /*<<< orphan*/  state; int /*<<< orphan*/  remote_bdaddr; int /*<<< orphan*/  scid; int /*<<< orphan*/  psm; int /*<<< orphan*/  encrypt; struct l2cap_pcb* next; } ;
struct bd_addr {int dummy; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  L2CAP_CONN_REF_RES ; 
 int /*<<< orphan*/  L2CAP_CONN_REQ ; 
 int /*<<< orphan*/  L2CAP_CONN_REQ_SIZE ; 
 int /*<<< orphan*/  L2CA_ACTION_CONN_CFM (struct l2cap_pcb*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 int /*<<< orphan*/  W4_L2CAP_CONNECT_RSP ; 
 scalar_t__ bd_addr_cmp (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 struct l2cap_pcb* l2cap_active_pcbs ; 
 scalar_t__ l2cap_signal (struct l2cap_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pbuf*) ; 

void lp_connect_cfm(struct bd_addr *bdaddr, u8_t encrypt_mode, err_t err)
{
	struct l2cap_pcb *pcb;
	struct pbuf *data;
	err_t ret;

	for(pcb = l2cap_active_pcbs; pcb != NULL; pcb = pcb->next) {
		if(bd_addr_cmp(&(pcb->remote_bdaddr), bdaddr)) {
			break;
		}
	}
	if(pcb == NULL) {
		/* Silently discard */
		LOG("lp_connect_cfm: Silently discard\n");
	} else {
		if(err == ERR_OK) {
			pcb->encrypt = encrypt_mode;
			/* Send l2cap_conn_req signal if no error */
			if((data = btpbuf_alloc(PBUF_RAW, L2CAP_CONN_REQ_SIZE, PBUF_RAM)) != NULL) {
				((u16_t *)data->payload)[0] = htole16(pcb->psm);
				((u16_t *)data->payload)[1] = htole16(pcb->scid);
				if((ret = l2cap_signal(pcb, L2CAP_CONN_REQ, 0, &(pcb->remote_bdaddr), data)) == ERR_OK) {
					pcb->state = W4_L2CAP_CONNECT_RSP;
				} else {
					L2CA_ACTION_CONN_CFM(pcb,L2CAP_CONN_REF_RES,0x0000,ret); /* No resources available? */
				}
				//LOG("lp_connect_cfm: l2cap_conn_req signal sent. err = %d\nPSM = 0x%x\nscid = 0x%x\nencrypt mode = 0x%x\n", err, pcb->psm, pcb->scid, pcb->encrypt);
			} else {
				ERROR("lp_connect_cfm: No resources available\n");
				L2CA_ACTION_CONN_CFM(pcb,L2CAP_CONN_REF_RES,0x0000,ret); /* No resources available */
			}
		} else {
			ERROR("lp_connect_cfm: Connection falied\n");
			L2CA_ACTION_CONN_CFM(pcb,L2CAP_CONN_REF_RES,0x0000,ret); /* No resources available */
		}
	}
}