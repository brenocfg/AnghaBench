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
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {scalar_t__ payload; } ;
struct l2cap_pcb {scalar_t__ state; scalar_t__ (* l2ca_disconnect_cfm ) (void*,struct l2cap_pcb*) ;int /*<<< orphan*/  remote_bdaddr; int /*<<< orphan*/  scid; int /*<<< orphan*/  dcid; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 scalar_t__ ERR_CONN ; 
 scalar_t__ ERR_MEM ; 
 scalar_t__ ERR_OK ; 
 scalar_t__ L2CAP_CONFIG ; 
 int /*<<< orphan*/  L2CAP_DISCONN_REQ ; 
 int /*<<< orphan*/  L2CAP_DISCONN_REQ_SIZE ; 
 scalar_t__ L2CAP_OPEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 scalar_t__ W4_L2CAP_DISCONNECT_RSP ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 scalar_t__ l2cap_signal (struct l2cap_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pbuf*) ; 

err_t l2ca_disconnect_req(struct l2cap_pcb *pcb, err_t (* l2ca_disconnect_cfm)(void *arg, struct l2cap_pcb *pcb))
{
	struct pbuf *data;
	err_t ret;

	if(pcb->state == L2CAP_OPEN || pcb->state == L2CAP_CONFIG) {
		if((data = btpbuf_alloc(PBUF_RAW, L2CAP_DISCONN_REQ_SIZE, PBUF_RAM)) == NULL) {
			ERROR("l2cap_disconnect_req: Could not allocate memory for pbuf\n");
			return ERR_MEM;
		}
		pcb->l2ca_disconnect_cfm = l2ca_disconnect_cfm;

		((u16_t *)data->payload)[0] = htole16(pcb->dcid);
		((u16_t *)data->payload)[1] = htole16(pcb->scid);

		ret = l2cap_signal(pcb, L2CAP_DISCONN_REQ, 0, &(pcb->remote_bdaddr), data);

		if(ret == ERR_OK) {
			pcb->state = W4_L2CAP_DISCONNECT_RSP;
		}
	} else {
		return ERR_CONN; /* Signal not supported in this state */
	}

	return ret;
}