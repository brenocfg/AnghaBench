#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union pptp_ctrl_union {int doff; int /*<<< orphan*/  messageType; int /*<<< orphan*/  magicCookie; int /*<<< orphan*/  packetType; } ;
typedef  size_t u_int16_t ;
struct tcphdr {int doff; int /*<<< orphan*/  messageType; int /*<<< orphan*/  magicCookie; int /*<<< orphan*/  packetType; } ;
struct sk_buff {unsigned int len; } ;
struct pptp_pkt_hdr {int doff; int /*<<< orphan*/  messageType; int /*<<< orphan*/  magicCookie; int /*<<< orphan*/  packetType; } ;
struct nf_ct_pptp_master {int sstate; int cstate; } ;
struct nf_conn {int dummy; } ;
struct PptpControlHeader {int doff; int /*<<< orphan*/  messageType; int /*<<< orphan*/  magicCookie; int /*<<< orphan*/  packetType; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  _tcph ;
typedef  int /*<<< orphan*/  _pptph ;
typedef  int /*<<< orphan*/  _ctlh ;
struct TYPE_3__ {struct nf_ct_pptp_master ct_pptp_info; } ;
struct TYPE_4__ {TYPE_1__ help; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CTINFO2DIR (int) ; 
 int IP_CT_DIR_ORIGINAL ; 
 int IP_CT_ESTABLISHED ; 
 int IP_CT_IS_REPLY ; 
 int NF_ACCEPT ; 
 scalar_t__ PPTP_MAGIC_COOKIE ; 
 size_t PPTP_MSG_MAX ; 
 scalar_t__ PPTP_PACKET_CONTROL ; 
 int /*<<< orphan*/  nf_pptp_lock ; 
 TYPE_2__* nfct_help (struct nf_conn*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int pptp_inbound_pkt (struct sk_buff*,union pptp_ctrl_union*,union pptp_ctrl_union*,unsigned int,struct nf_conn*,int) ; 
 unsigned int* pptp_msg_size ; 
 int pptp_outbound_pkt (struct sk_buff*,union pptp_ctrl_union*,union pptp_ctrl_union*,unsigned int,struct nf_conn*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 void* skb_header_pointer (struct sk_buff*,unsigned int,unsigned int,union pptp_ctrl_union*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
conntrack_pptp_help(struct sk_buff *skb, unsigned int protoff,
		    struct nf_conn *ct, enum ip_conntrack_info ctinfo)

{
	int dir = CTINFO2DIR(ctinfo);
	const struct nf_ct_pptp_master *info = &nfct_help(ct)->help.ct_pptp_info;
	const struct tcphdr *tcph;
	struct tcphdr _tcph;
	const struct pptp_pkt_hdr *pptph;
	struct pptp_pkt_hdr _pptph;
	struct PptpControlHeader _ctlh, *ctlh;
	union pptp_ctrl_union _pptpReq, *pptpReq;
	unsigned int tcplen = skb->len - protoff;
	unsigned int datalen, reqlen, nexthdr_off;
	int oldsstate, oldcstate;
	int ret;
	u_int16_t msg;

	/* don't do any tracking before tcp handshake complete */
	if (ctinfo != IP_CT_ESTABLISHED &&
	    ctinfo != IP_CT_ESTABLISHED + IP_CT_IS_REPLY)
		return NF_ACCEPT;

	nexthdr_off = protoff;
	tcph = skb_header_pointer(skb, nexthdr_off, sizeof(_tcph), &_tcph);
	BUG_ON(!tcph);
	nexthdr_off += tcph->doff * 4;
	datalen = tcplen - tcph->doff * 4;

	pptph = skb_header_pointer(skb, nexthdr_off, sizeof(_pptph), &_pptph);
	if (!pptph) {
		pr_debug("no full PPTP header, can't track\n");
		return NF_ACCEPT;
	}
	nexthdr_off += sizeof(_pptph);
	datalen -= sizeof(_pptph);

	/* if it's not a control message we can't do anything with it */
	if (ntohs(pptph->packetType) != PPTP_PACKET_CONTROL ||
	    ntohl(pptph->magicCookie) != PPTP_MAGIC_COOKIE) {
		pr_debug("not a control packet\n");
		return NF_ACCEPT;
	}

	ctlh = skb_header_pointer(skb, nexthdr_off, sizeof(_ctlh), &_ctlh);
	if (!ctlh)
		return NF_ACCEPT;
	nexthdr_off += sizeof(_ctlh);
	datalen -= sizeof(_ctlh);

	reqlen = datalen;
	msg = ntohs(ctlh->messageType);
	if (msg > 0 && msg <= PPTP_MSG_MAX && reqlen < pptp_msg_size[msg])
		return NF_ACCEPT;
	if (reqlen > sizeof(*pptpReq))
		reqlen = sizeof(*pptpReq);

	pptpReq = skb_header_pointer(skb, nexthdr_off, reqlen, &_pptpReq);
	if (!pptpReq)
		return NF_ACCEPT;

	oldsstate = info->sstate;
	oldcstate = info->cstate;

	spin_lock_bh(&nf_pptp_lock);

	/* FIXME: We just blindly assume that the control connection is always
	 * established from PNS->PAC.  However, RFC makes no guarantee */
	if (dir == IP_CT_DIR_ORIGINAL)
		/* client -> server (PNS -> PAC) */
		ret = pptp_outbound_pkt(skb, ctlh, pptpReq, reqlen, ct,
					ctinfo);
	else
		/* server -> client (PAC -> PNS) */
		ret = pptp_inbound_pkt(skb, ctlh, pptpReq, reqlen, ct,
				       ctinfo);
	pr_debug("sstate: %d->%d, cstate: %d->%d\n",
		 oldsstate, info->sstate, oldcstate, info->cstate);
	spin_unlock_bh(&nf_pptp_lock);

	return ret;
}