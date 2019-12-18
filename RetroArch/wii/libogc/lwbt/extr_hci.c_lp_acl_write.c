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
typedef  int u8_t ;
typedef  int u16_t ;
struct pbuf {int len; scalar_t__ payload; } ;
struct hci_link {int len; int pb; int connhdl; struct pbuf* p; } ;
struct hci_acl_hdr {void* len; void* connhdl_pb_bc; } ;
struct bd_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_2__ {scalar_t__ acl_max_pkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_CONN ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int HCI_ACL_DATA_PACKET ; 
 scalar_t__ HCI_ACL_HDR_LEN ; 
 int /*<<< orphan*/  LOG (char*,...) ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_chain (struct pbuf*,struct pbuf*) ; 
 struct pbuf* btpbuf_dechain (struct pbuf*) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  btpbuf_ref (struct pbuf*) ; 
 struct pbuf* btpbuf_take (struct pbuf*) ; 
 TYPE_1__* hci_dev ; 
 struct hci_link* hci_get_link (struct bd_addr*) ; 
 void* htole16 (int) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int) ; 

err_t lp_acl_write(struct bd_addr *bdaddr,struct pbuf *p,u16_t len,u8_t pb)
{
	u16_t connhdlpbbc;
	struct hci_link *link;
	struct hci_acl_hdr *aclhdr;
	struct pbuf *q;

	link = hci_get_link(bdaddr);
	if(link==NULL) {
		ERROR("lp_acl_write: ACL connection does not exist\n");
		return ERR_CONN;
	}

	if(hci_dev->acl_max_pkt==0) {
		if(p != NULL) {
			/* Packet can be queued? */
			if(link->p != NULL) {
				LOG("lp_acl_write: Host buffer full. Dropped packet\n");
				return ERR_OK; /* Drop packet */
			} else {
				/* Copy PBUF_REF referenced payloads into PBUF_RAM */
				p = btpbuf_take(p);
				/* Remember pbuf to queue, if any */
				link->p = p;
				link->len = len;
				link->pb = pb;
				/* Pbufs are queued, increase the reference count */
				btpbuf_ref(p);
				LOG("lp_acl_write: Host queued packet %p\n", (void *)p);
			}
		}
	}

	if((q=btpbuf_alloc(PBUF_RAW,HCI_ACL_HDR_LEN+1,PBUF_RAM))==NULL) {
		ERROR("lp_acl_write: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}

	btpbuf_chain(q,p);
	((u8_t*)q->payload)[0] = HCI_ACL_DATA_PACKET;

	aclhdr = (void*)((u8_t*)q->payload+1);
	//aclhdr->connhdl_pb_bc = CONNPBBC(link->connhdl,pb,0);
	connhdlpbbc = link->connhdl; /* Received from connection complete event */
	connhdlpbbc |= (pb<<12); /* Packet boundary flag */
	connhdlpbbc &= 0x3FFF; /* Point-to-point */
	aclhdr->connhdl_pb_bc = htole16(connhdlpbbc);
	aclhdr->len = htole16(len);

	physbusif_output(q,(q->len+len));
	--hci_dev->acl_max_pkt;

	p = btpbuf_dechain(q);
	btpbuf_free(q);
	return ERR_OK;
}