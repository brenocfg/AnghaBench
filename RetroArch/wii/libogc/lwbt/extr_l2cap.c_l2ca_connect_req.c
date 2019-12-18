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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {scalar_t__ payload; } ;
struct TYPE_2__ {int /*<<< orphan*/  l2capcfg; } ;
struct l2cap_pcb {int /*<<< orphan*/  state; int /*<<< orphan*/  remote_bdaddr; int /*<<< orphan*/  scid; TYPE_1__ cfg; int /*<<< orphan*/  (* l2ca_connect_cfm ) (void*,struct l2cap_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  psm; } ;
struct bd_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  L2CAP_CFG_IR ; 
 int /*<<< orphan*/  L2CAP_CONN_REQ ; 
 int /*<<< orphan*/  L2CAP_CONN_REQ_SIZE ; 
 int /*<<< orphan*/  L2CAP_REG (int /*<<< orphan*/ *,struct l2cap_pcb*) ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 int /*<<< orphan*/  W4_L2CAP_CONNECT_RSP ; 
 int /*<<< orphan*/  bd_addr_set (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_active_pcbs ; 
 int /*<<< orphan*/  l2cap_cid_alloc () ; 
 int /*<<< orphan*/  l2cap_signal (struct l2cap_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pbuf*) ; 
 int /*<<< orphan*/  lp_connect_req (struct bd_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp_is_connected (struct bd_addr*) ; 

err_t l2ca_connect_req(struct l2cap_pcb *pcb, struct bd_addr *bdaddr, u16_t psm,
                 u8_t role_switch, err_t (* l2ca_connect_cfm)(void *arg, struct l2cap_pcb *lpcb,
					    u16_t result, u16_t status))
{
	err_t ret;
	struct pbuf *data;

	if(bdaddr != NULL) {
		bd_addr_set(&(pcb->remote_bdaddr),bdaddr);
	} else {
		return ERR_VAL;
	}

	pcb->psm = psm;
	pcb->l2ca_connect_cfm = l2ca_connect_cfm;
	pcb->scid = l2cap_cid_alloc();

	pcb->cfg.l2capcfg |= L2CAP_CFG_IR; /* We are the initiator of this connection */

	if(!lp_is_connected(bdaddr)) {
		ret = lp_connect_req(bdaddr, role_switch); /* Create ACL link w pcb state == CLOSED */
	} else {
		if((data = btpbuf_alloc(PBUF_RAW, L2CAP_CONN_REQ_SIZE, PBUF_RAM)) == NULL) {
			ERROR("l2cap_connect_req: Could not allocate memory for pbuf\n");
			return ERR_MEM;
		}
		((u16_t *)data->payload)[0] = htole16(psm);
		((u16_t *)data->payload)[1] = htole16(pcb->scid);
		ret = l2cap_signal(pcb, L2CAP_CONN_REQ, 0, &(pcb->remote_bdaddr), data); /* Send l2cap_conn_req signal */

		pcb->state = W4_L2CAP_CONNECT_RSP;
	}

	L2CAP_REG(&(l2cap_active_pcbs), pcb);

	return ret;
}