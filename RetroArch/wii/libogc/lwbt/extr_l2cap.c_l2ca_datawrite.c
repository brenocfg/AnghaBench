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
struct pbuf {scalar_t__ tot_len; struct l2cap_hdr* payload; } ;
struct TYPE_2__ {scalar_t__ outmtu; } ;
struct l2cap_pcb {scalar_t__ state; scalar_t__ dcid; int /*<<< orphan*/  remote_bdaddr; TYPE_1__ cfg; } ;
struct l2cap_hdr {void* len; void* cid; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_BUF ; 
 int /*<<< orphan*/  ERR_CONN ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 scalar_t__ L2CAP_HDR_LEN ; 
 scalar_t__ L2CAP_OPEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_chain (struct pbuf*,struct pbuf*) ; 
 struct pbuf* btpbuf_dechain (struct pbuf*) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 void* htole16 (scalar_t__) ; 
 int /*<<< orphan*/  l2cap_write (int /*<<< orphan*/ *,struct pbuf*,scalar_t__) ; 

err_t l2ca_datawrite(struct l2cap_pcb *pcb, struct pbuf *p)
{
	err_t ret;
	struct l2cap_hdr *l2caphdr;
	struct pbuf *q;

	if(pcb->state != L2CAP_OPEN) {
		ERROR("l2cap_datawrite: State != L2CAP_OPEN. Dropping data\n");
		return ERR_CONN;
	}

	/* Build L2CAP header */
	if((q = btpbuf_alloc(PBUF_RAW, L2CAP_HDR_LEN, PBUF_RAM)) == NULL) {
		ERROR("l2cap_datawrite: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}
	btpbuf_chain(q, p);

	l2caphdr = q->payload;
	l2caphdr->cid = htole16(pcb->dcid);

	/* If length of the data exceeds the OutMTU then only the first OutMTU bytes are sent */
	if(p->tot_len > pcb->cfg.outmtu) {
		/* Send peer L2CAP data */
		l2caphdr->len = htole16(pcb->cfg.outmtu);
		if((ret = l2cap_write(&(pcb->remote_bdaddr), q, pcb->cfg.outmtu + L2CAP_HDR_LEN)) == ERR_OK) {
			//LOG("l2cap_datawrite: Length of data exceeds the OutMTU p->tot_len = %d\n", p->tot_len);
			ret = ERR_BUF; /* Length of data exceeds the OutMTU */
		}
	} else {
		/* Send peer L2CAP data */
		l2caphdr->len = htole16(p->tot_len);
		//LOG("l2cap_datawrite: q->tot_len = %d\n", q->tot_len);
		ret = l2cap_write(&(pcb->remote_bdaddr), q, q->tot_len);
	}

	/* Free L2CAP header. Higher layers will handle rest of packet */
	p = btpbuf_dechain(q);
	btpbuf_free(q);

	return ret;
}