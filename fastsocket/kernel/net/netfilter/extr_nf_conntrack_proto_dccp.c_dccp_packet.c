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
typedef  size_t u_int8_t ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int* role; size_t state; int last_dir; size_t last_pkt; void* handshake_seq; } ;
struct TYPE_4__ {TYPE_1__ dccp; } ;
struct nf_conn {int /*<<< orphan*/  lock; TYPE_2__ proto; int /*<<< orphan*/  status; } ;
struct net {int dummy; } ;
struct dccp_net {int /*<<< orphan*/ * dccp_timeout; } ;
struct dccp_hdr {size_t dccph_type; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  enum ct_dccp_roles { ____Placeholder_ct_dccp_roles } ct_dccp_roles ;
typedef  int /*<<< orphan*/  _dh ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int CTINFO2DIR (int) ; 
#define  CT_DCCP_IGNORE 132 
#define  CT_DCCP_INVALID 131 
#define  CT_DCCP_PARTOPEN 130 
#define  CT_DCCP_REQUEST 129 
#define  CT_DCCP_RESPOND 128 
 void* CT_DCCP_ROLE_CLIENT ; 
 int CT_DCCP_ROLE_SERVER ; 
 size_t CT_DCCP_TIMEWAIT ; 
 size_t DCCP_PKT_ACK ; 
 size_t DCCP_PKT_REQUEST ; 
 size_t DCCP_PKT_RESET ; 
 size_t DCCP_PKT_RESPONSE ; 
 int /*<<< orphan*/  IPCT_PROTOINFO ; 
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 int /*<<< orphan*/  IPS_ASSURED_BIT ; 
 int /*<<< orphan*/  IPS_SEEN_REPLY_BIT ; 
 int /*<<< orphan*/  LOG_INVALID (struct net*,int /*<<< orphan*/ ) ; 
 int NF_ACCEPT ; 
 void* dccp_ack_seq (struct dccp_hdr*) ; 
 void* dccp_hdr_seq (struct dccp_hdr*) ; 
 struct dccp_net* dccp_pernet (struct net*) ; 
 size_t*** dccp_state_table ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_kill_acct (struct nf_conn*,int,struct sk_buff const*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_refresh_acct (struct nf_conn*,int,struct sk_buff const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_log_packet (size_t,int /*<<< orphan*/ ,struct sk_buff const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dccp_hdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct dccp_hdr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dccp_packet(struct nf_conn *ct, const struct sk_buff *skb,
		       unsigned int dataoff, enum ip_conntrack_info ctinfo,
		       u_int8_t pf, unsigned int hooknum)
{
	struct net *net = nf_ct_net(ct);
	struct dccp_net *dn;
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	struct dccp_hdr _dh, *dh;
	u_int8_t type, old_state, new_state;
	enum ct_dccp_roles role;

	dh = skb_header_pointer(skb, dataoff, sizeof(_dh), &_dh);
	BUG_ON(dh == NULL);
	type = dh->dccph_type;

	if (type == DCCP_PKT_RESET &&
	    !test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) {
		/* Tear down connection immediately if only reply is a RESET */
		nf_ct_kill_acct(ct, ctinfo, skb);
		return NF_ACCEPT;
	}

	spin_lock_bh(&ct->lock);

	role = ct->proto.dccp.role[dir];
	old_state = ct->proto.dccp.state;
	new_state = dccp_state_table[role][type][old_state];

	switch (new_state) {
	case CT_DCCP_REQUEST:
		if (old_state == CT_DCCP_TIMEWAIT &&
		    role == CT_DCCP_ROLE_SERVER) {
			/* Reincarnation in the reverse direction: reopen and
			 * reverse client/server roles. */
			ct->proto.dccp.role[dir] = CT_DCCP_ROLE_CLIENT;
			ct->proto.dccp.role[!dir] = CT_DCCP_ROLE_SERVER;
		}
		break;
	case CT_DCCP_RESPOND:
		if (old_state == CT_DCCP_REQUEST)
			ct->proto.dccp.handshake_seq = dccp_hdr_seq(dh);
		break;
	case CT_DCCP_PARTOPEN:
		if (old_state == CT_DCCP_RESPOND &&
		    type == DCCP_PKT_ACK &&
		    dccp_ack_seq(dh) == ct->proto.dccp.handshake_seq)
			set_bit(IPS_ASSURED_BIT, &ct->status);
		break;
	case CT_DCCP_IGNORE:
		/*
		 * Connection tracking might be out of sync, so we ignore
		 * packets that might establish a new connection and resync
		 * if the server responds with a valid Response.
		 */
		if (ct->proto.dccp.last_dir == !dir &&
		    ct->proto.dccp.last_pkt == DCCP_PKT_REQUEST &&
		    type == DCCP_PKT_RESPONSE) {
			ct->proto.dccp.role[!dir] = CT_DCCP_ROLE_CLIENT;
			ct->proto.dccp.role[dir] = CT_DCCP_ROLE_SERVER;
			ct->proto.dccp.handshake_seq = dccp_hdr_seq(dh);
			new_state = CT_DCCP_RESPOND;
			break;
		}
		ct->proto.dccp.last_dir = dir;
		ct->proto.dccp.last_pkt = type;

		spin_unlock_bh(&ct->lock);
		if (LOG_INVALID(net, IPPROTO_DCCP))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				      "nf_ct_dccp: invalid packet ignored ");
		return NF_ACCEPT;
	case CT_DCCP_INVALID:
		spin_unlock_bh(&ct->lock);
		if (LOG_INVALID(net, IPPROTO_DCCP))
			nf_log_packet(pf, 0, skb, NULL, NULL, NULL,
				      "nf_ct_dccp: invalid state transition ");
		return -NF_ACCEPT;
	}

	ct->proto.dccp.last_dir = dir;
	ct->proto.dccp.last_pkt = type;
	ct->proto.dccp.state = new_state;
	spin_unlock_bh(&ct->lock);

	if (new_state != old_state)
		nf_conntrack_event_cache(IPCT_PROTOINFO, ct);

	dn = dccp_pernet(net);
	nf_ct_refresh_acct(ct, ctinfo, skb, dn->dccp_timeout[new_state]);

	return NF_ACCEPT;
}