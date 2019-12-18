#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct sk_buff {int dummy; } ;
struct nf_ct_h323_master {scalar_t__** rtp_port; } ;
struct TYPE_19__ {scalar_t__ port; } ;
struct TYPE_20__ {TYPE_12__ udp; } ;
struct TYPE_18__ {int /*<<< orphan*/  ip; } ;
struct TYPE_21__ {TYPE_13__ u; TYPE_11__ u3; } ;
struct TYPE_31__ {scalar_t__ port; } ;
struct TYPE_32__ {TYPE_8__ udp; } ;
struct TYPE_30__ {int /*<<< orphan*/  ip; } ;
struct TYPE_17__ {TYPE_9__ u; TYPE_7__ u3; } ;
struct TYPE_22__ {TYPE_14__ dst; TYPE_10__ src; } ;
struct TYPE_25__ {scalar_t__ port; } ;
struct TYPE_26__ {TYPE_2__ udp; } ;
struct nf_conntrack_expect {int dir; TYPE_15__ tuple; void* expectfn; TYPE_3__ saved_proto; } ;
struct nf_conn {TYPE_6__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  scalar_t__ __be16 ;
struct TYPE_27__ {int /*<<< orphan*/  u3; } ;
struct TYPE_28__ {TYPE_4__ dst; } ;
struct TYPE_29__ {TYPE_5__ tuple; } ;
struct TYPE_24__ {struct nf_ct_h323_master ct_h323_info; } ;
struct TYPE_23__ {TYPE_1__ help; } ;
typedef  int /*<<< orphan*/  H245_TransportAddress ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int H323_RTP_CHANNEL_MAX ; 
 scalar_t__ htons (int) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 void* nf_nat_follow_master ; 
 TYPE_16__* nfct_help (struct nf_conn*) ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ set_h245_addr (struct sk_buff*,unsigned char**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int nat_rtp_rtcp(struct sk_buff *skb, struct nf_conn *ct,
			enum ip_conntrack_info ctinfo,
			unsigned char **data, int dataoff,
			H245_TransportAddress *taddr,
			__be16 port, __be16 rtp_port,
			struct nf_conntrack_expect *rtp_exp,
			struct nf_conntrack_expect *rtcp_exp)
{
	struct nf_ct_h323_master *info = &nfct_help(ct)->help.ct_h323_info;
	int dir = CTINFO2DIR(ctinfo);
	int i;
	u_int16_t nated_port;

	/* Set expectations for NAT */
	rtp_exp->saved_proto.udp.port = rtp_exp->tuple.dst.u.udp.port;
	rtp_exp->expectfn = nf_nat_follow_master;
	rtp_exp->dir = !dir;
	rtcp_exp->saved_proto.udp.port = rtcp_exp->tuple.dst.u.udp.port;
	rtcp_exp->expectfn = nf_nat_follow_master;
	rtcp_exp->dir = !dir;

	/* Lookup existing expects */
	for (i = 0; i < H323_RTP_CHANNEL_MAX; i++) {
		if (info->rtp_port[i][dir] == rtp_port) {
			/* Expected */

			/* Use allocated ports first. This will refresh
			 * the expects */
			rtp_exp->tuple.dst.u.udp.port = info->rtp_port[i][dir];
			rtcp_exp->tuple.dst.u.udp.port =
			    htons(ntohs(info->rtp_port[i][dir]) + 1);
			break;
		} else if (info->rtp_port[i][dir] == 0) {
			/* Not expected */
			break;
		}
	}

	/* Run out of expectations */
	if (i >= H323_RTP_CHANNEL_MAX) {
		if (net_ratelimit())
			printk("nf_nat_h323: out of expectations\n");
		return 0;
	}

	/* Try to get a pair of ports. */
	for (nated_port = ntohs(rtp_exp->tuple.dst.u.udp.port);
	     nated_port != 0; nated_port += 2) {
		rtp_exp->tuple.dst.u.udp.port = htons(nated_port);
		if (nf_ct_expect_related(rtp_exp) == 0) {
			rtcp_exp->tuple.dst.u.udp.port =
			    htons(nated_port + 1);
			if (nf_ct_expect_related(rtcp_exp) == 0)
				break;
			nf_ct_unexpect_related(rtp_exp);
		}
	}

	if (nated_port == 0) {	/* No port available */
		if (net_ratelimit())
			printk("nf_nat_h323: out of RTP ports\n");
		return 0;
	}

	/* Modify signal */
	if (set_h245_addr(skb, data, dataoff, taddr,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  htons((port & htons(1)) ? nated_port + 1 :
						    nated_port)) == 0) {
		/* Save ports */
		info->rtp_port[i][dir] = rtp_port;
		info->rtp_port[i][!dir] = htons(nated_port);
	} else {
		nf_ct_unexpect_related(rtp_exp);
		nf_ct_unexpect_related(rtcp_exp);
		return -1;
	}

	/* Success */
	pr_debug("nf_nat_h323: expect RTP %pI4:%hu->%pI4:%hu\n",
		 &rtp_exp->tuple.src.u3.ip,
		 ntohs(rtp_exp->tuple.src.u.udp.port),
		 &rtp_exp->tuple.dst.u3.ip,
		 ntohs(rtp_exp->tuple.dst.u.udp.port));
	pr_debug("nf_nat_h323: expect RTCP %pI4:%hu->%pI4:%hu\n",
		 &rtcp_exp->tuple.src.u3.ip,
		 ntohs(rtcp_exp->tuple.src.u.udp.port),
		 &rtcp_exp->tuple.dst.u3.ip,
		 ntohs(rtcp_exp->tuple.dst.u.udp.port));

	return 0;
}