#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {scalar_t__ tot_len; struct hci_acl_hdr* payload; } ;
struct l2cap_seg {scalar_t__ len; struct pbuf* p; TYPE_1__* pcb; struct hci_acl_hdr* l2caphdr; int /*<<< orphan*/  bdaddr; struct l2cap_seg* next; } ;
struct hci_acl_hdr {int len; int connhdl_pb_bc; int cid; } ;
struct bd_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_3__ {int scid; struct TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 scalar_t__ HCI_ACL_HDR_LEN ; 
 int L2CAP_ACL_CONT ; 
 int L2CAP_ACL_START ; 
 int /*<<< orphan*/  L2CAP_CMD_REJ ; 
 int /*<<< orphan*/  L2CAP_CMD_REJ_SIZE ; 
#define  L2CAP_CONNLESS_CID 130 
 scalar_t__ L2CAP_HDR_LEN ; 
 int const L2CAP_INVALID_CID ; 
#define  L2CAP_NULL_CID 129 
 int /*<<< orphan*/  L2CAP_SEG_REG (struct l2cap_seg**,struct l2cap_seg*) ; 
 int /*<<< orphan*/  L2CAP_SEG_RMV (struct l2cap_seg**,struct l2cap_seg*) ; 
#define  L2CAP_SIG_CID 128 
 int /*<<< orphan*/  L2CA_ACTION_RECV (TYPE_1__*,struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 scalar_t__ bd_addr_cmp (struct bd_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_addr_set (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct l2cap_seg* btmemb_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct l2cap_seg*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_chain (struct pbuf*,struct pbuf*) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  btpbuf_header (struct pbuf*,scalar_t__) ; 
 int /*<<< orphan*/  btpbuf_realloc (struct pbuf*,int) ; 
 int /*<<< orphan*/  htole16 (int const) ; 
 TYPE_1__* l2cap_active_pcbs ; 
 struct l2cap_seg* l2cap_insegs ; 
 int /*<<< orphan*/  l2cap_next_sigid () ; 
 int /*<<< orphan*/  l2cap_process_sig (struct pbuf*,struct hci_acl_hdr*,struct bd_addr*) ; 
 int /*<<< orphan*/  l2cap_segs ; 
 int /*<<< orphan*/  l2cap_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bd_addr*,struct pbuf*) ; 
 void* le16toh (int) ; 

void l2cap_input(struct pbuf *p, struct bd_addr *bdaddr)
{
	struct l2cap_seg *inseg;
	struct hci_acl_hdr *aclhdr;
	struct pbuf *data;
	err_t ret;

	(void)ret;

	btpbuf_header(p, HCI_ACL_HDR_LEN);
	aclhdr = p->payload;
	btpbuf_header(p, -HCI_ACL_HDR_LEN);

	btpbuf_realloc(p, aclhdr->len);

	for(inseg = l2cap_insegs; inseg != NULL; inseg = inseg->next) {
		if(bd_addr_cmp(bdaddr, &(inseg->bdaddr))) {
			break;
		}
	}

	aclhdr->connhdl_pb_bc = le16toh(aclhdr->connhdl_pb_bc);
	aclhdr->len = le16toh(aclhdr->len);
	/* Reassembly procedures */
	/* Check if continuing fragment or start of L2CAP packet */
	if(((aclhdr->connhdl_pb_bc >> 12) & 0x03)== L2CAP_ACL_CONT) { /* Continuing fragment */
		if(inseg == NULL)  {
			/* Discard packet */
			LOG("l2cap_input: Continuing fragment. Discard packet\n");
			btpbuf_free(p);
			return;
		} else if(inseg->p->tot_len + p->tot_len > inseg->len) { /* Check if length of
								segment exceeds
								l2cap header length */
			/* Discard packet */
			LOG("l2cap_input: Continuing fragment. Length exceeds L2CAP hdr length. Discard packet\n");
			btpbuf_free(inseg->p);
			L2CAP_SEG_RMV(&(l2cap_insegs), inseg);
			btmemb_free(&l2cap_segs, inseg);

			btpbuf_free(p);
			return;
		}
		/* Add pbuf to segement */
		btpbuf_chain(inseg->p, p);
		btpbuf_free(p);

	} else if(((aclhdr->connhdl_pb_bc >> 12) & 0x03) == L2CAP_ACL_START) { /* Start of L2CAP packet */
		//LOG("l2cap_input: Start of L2CAP packet p->len = %d, p->tot_len = %d\n", p->len, p->tot_len);
		if(inseg != NULL) { /* Check if there are segments missing in a previous packet */
			/* Discard previous packet */
			LOG("l2cap_input: Start of L2CAP packet. Discard previous packet\n");
			btpbuf_free(inseg->p);
		} else {
			inseg = btmemb_alloc(&l2cap_segs);
			bd_addr_set(&(inseg->bdaddr), bdaddr);
			L2CAP_SEG_REG(&(l2cap_insegs), inseg);
		}
		inseg->p = p;
		inseg->l2caphdr = p->payload;
		inseg->l2caphdr->cid = le16toh(inseg->l2caphdr->cid);
		inseg->l2caphdr->len = le16toh(inseg->l2caphdr->len);

		inseg->len = inseg->l2caphdr->len + L2CAP_HDR_LEN;
		for(inseg->pcb = l2cap_active_pcbs; inseg->pcb != NULL; inseg->pcb = inseg->pcb->next) {
			if(inseg->pcb->scid == inseg->l2caphdr->cid) {
				break; /* found */
			}
		}
	} else {
		/* Discard packet */
		LOG("l2cap_input: Discard packet\n");
		btpbuf_free(inseg->p);
		L2CAP_SEG_RMV(&(l2cap_insegs), inseg);
		btmemb_free(&l2cap_segs, inseg);

		btpbuf_free(p);
		return;
	}
	if(inseg->p->tot_len < inseg->len) {
		LOG("l2cap_input: Get continuing segments\n");
		return; /* Get continuing segments */
	}

	/* Handle packet */
	switch(inseg->l2caphdr->cid) {
		case L2CAP_NULL_CID:
			/* Illegal */
			LOG("l2cap_input: Illegal null cid\n");
			btpbuf_free(inseg->p);
			break;
		case L2CAP_SIG_CID:
			btpbuf_header(inseg->p, -L2CAP_HDR_LEN);
			l2cap_process_sig(inseg->p, inseg->l2caphdr, bdaddr);
			btpbuf_free(inseg->p);
			break;
		case L2CAP_CONNLESS_CID:
			/* Not needed by PAN, LAN access or DUN profiles */
			btpbuf_free(inseg->p);
			break;
		default:
			if(inseg->l2caphdr->cid < 0x0040 || inseg->pcb == NULL) {
				/* Reserved for specific L2CAP functions or channel does not exist */
				/* Alloc size of reason in cmd rej */
				if((data = btpbuf_alloc(PBUF_RAW, L2CAP_CMD_REJ_SIZE+4, PBUF_RAM)) != NULL) {
					((u16_t *)data->payload)[0] = htole16(L2CAP_INVALID_CID);
					((u16_t *)data->payload)[1] = htole16(inseg->l2caphdr->cid);
					((u16_t *)data->payload)[2] = htole16(L2CAP_NULL_CID);

					ret = l2cap_signal(NULL, L2CAP_CMD_REJ, l2cap_next_sigid(), bdaddr, data);
				}
				btpbuf_free(inseg->p);
				break;
			}

			btpbuf_header(inseg->p, -L2CAP_HDR_LEN);

			/* Forward packet to higher layer */
			LOG("l2cap_input: Forward packet to higher layer\n");
			/*
			LOG("l2cap_input: Remote BD address: 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x\n",
							   inseg->pcb->remote_bdaddr.addr[5],
							   inseg->pcb->remote_bdaddr.addr[4],
							   inseg->pcb->remote_bdaddr.addr[3],
							   inseg->pcb->remote_bdaddr.addr[2],
							   inseg->pcb->remote_bdaddr.addr[1],
							   inseg->pcb->remote_bdaddr.addr[0]));
			*/
			L2CA_ACTION_RECV(inseg->pcb,inseg->p,ERR_OK,ret);
			break;
	}

	/* Remove input segment */
	L2CAP_SEG_RMV(&(l2cap_insegs), inseg);
	btmemb_free(&l2cap_segs, inseg);
}