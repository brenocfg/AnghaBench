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
typedef  int /*<<< orphan*/  u8 ;
struct rfcomm_session {scalar_t__ cfc; int /*<<< orphan*/  initiator; } ;
struct rfcomm_pn {int flow_ctrl; void* mtu; scalar_t__ credits; scalar_t__ max_retrans; scalar_t__ ack_timer; int /*<<< orphan*/  priority; int /*<<< orphan*/  dlci; } ;
struct rfcomm_mcc {void* len; int /*<<< orphan*/  type; } ;
struct rfcomm_hdr {void* len; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  addr; } ;
struct rfcomm_dlc {scalar_t__ mtu; int /*<<< orphan*/  priority; int /*<<< orphan*/  dlci; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RFCOMM_DEFAULT_CREDITS ; 
 int /*<<< orphan*/  RFCOMM_PN ; 
 int /*<<< orphan*/  RFCOMM_UIH ; 
 int /*<<< orphan*/  __addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __fcs (int /*<<< orphan*/ *) ; 
 void* __len8 (int) ; 
 int /*<<< orphan*/  __mcc_type (int,int /*<<< orphan*/ ) ; 
 scalar_t__ channel_mtu ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int rfcomm_send_frame (struct rfcomm_session*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rfcomm_send_pn(struct rfcomm_session *s, int cr, struct rfcomm_dlc *d)
{
	struct rfcomm_hdr *hdr;
	struct rfcomm_mcc *mcc;
	struct rfcomm_pn  *pn;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d dlci %d mtu %d", s, cr, d->dlci, d->mtu);

	hdr = (void *) ptr; ptr += sizeof(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(sizeof(*mcc) + sizeof(*pn));

	mcc = (void *) ptr; ptr += sizeof(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_PN);
	mcc->len  = __len8(sizeof(*pn));

	pn = (void *) ptr; ptr += sizeof(*pn);
	pn->dlci        = d->dlci;
	pn->priority    = d->priority;
	pn->ack_timer   = 0;
	pn->max_retrans = 0;

	if (s->cfc) {
		pn->flow_ctrl = cr ? 0xf0 : 0xe0;
		pn->credits = RFCOMM_DEFAULT_CREDITS;
	} else {
		pn->flow_ctrl = 0;
		pn->credits   = 0;
	}

	if (cr && channel_mtu >= 0)
		pn->mtu = cpu_to_le16(channel_mtu);
	else
		pn->mtu = cpu_to_le16(d->mtu);

	*ptr = __fcs(buf); ptr++;

	return rfcomm_send_frame(s, buf, ptr - buf);
}