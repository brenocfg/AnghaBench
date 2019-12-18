#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
union nf_inet_addr {scalar_t__ ip; } ;
typedef  scalar_t__ u_int16_t ;
struct sk_buff {int dummy; } ;
struct TYPE_16__ {scalar_t__ port; } ;
struct TYPE_17__ {TYPE_12__ udp; } ;
struct TYPE_25__ {scalar_t__ port; } ;
struct TYPE_26__ {TYPE_8__ udp; } ;
struct TYPE_24__ {scalar_t__ ip; } ;
struct TYPE_14__ {TYPE_9__ u; TYPE_7__ u3; } ;
struct TYPE_15__ {TYPE_10__ dst; } ;
struct nf_conntrack_expect {scalar_t__ saved_ip; int dir; TYPE_13__ saved_proto; TYPE_11__ tuple; void* expectfn; } ;
struct nf_conn {TYPE_6__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_20__ {scalar_t__ ip; } ;
struct TYPE_21__ {TYPE_3__ u3; } ;
struct TYPE_18__ {scalar_t__ ip; } ;
struct TYPE_19__ {TYPE_1__ u3; } ;
struct TYPE_22__ {TYPE_4__ dst; TYPE_2__ src; } ;
struct TYPE_23__ {TYPE_5__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  ip_nat_sdp_port (struct sk_buff*,char const**,unsigned int*,unsigned int,unsigned int,scalar_t__) ; 
 void* ip_nat_sip_expected ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 scalar_t__ ntohs (scalar_t__) ; 

__attribute__((used)) static unsigned int ip_nat_sdp_media(struct sk_buff *skb,
				     const char **dptr,
				     unsigned int *datalen,
				     struct nf_conntrack_expect *rtp_exp,
				     struct nf_conntrack_expect *rtcp_exp,
				     unsigned int mediaoff,
				     unsigned int medialen,
				     union nf_inet_addr *rtp_addr)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	u_int16_t port;

	/* Connection will come from reply */
	if (ct->tuplehash[dir].tuple.src.u3.ip ==
	    ct->tuplehash[!dir].tuple.dst.u3.ip)
		rtp_addr->ip = rtp_exp->tuple.dst.u3.ip;
	else
		rtp_addr->ip = ct->tuplehash[!dir].tuple.dst.u3.ip;

	rtp_exp->saved_ip = rtp_exp->tuple.dst.u3.ip;
	rtp_exp->tuple.dst.u3.ip = rtp_addr->ip;
	rtp_exp->saved_proto.udp.port = rtp_exp->tuple.dst.u.udp.port;
	rtp_exp->dir = !dir;
	rtp_exp->expectfn = ip_nat_sip_expected;

	rtcp_exp->saved_ip = rtcp_exp->tuple.dst.u3.ip;
	rtcp_exp->tuple.dst.u3.ip = rtp_addr->ip;
	rtcp_exp->saved_proto.udp.port = rtcp_exp->tuple.dst.u.udp.port;
	rtcp_exp->dir = !dir;
	rtcp_exp->expectfn = ip_nat_sip_expected;

	/* Try to get same pair of ports: if not, try to change them. */
	for (port = ntohs(rtp_exp->tuple.dst.u.udp.port);
	     port != 0; port += 2) {
		rtp_exp->tuple.dst.u.udp.port = htons(port);
		if (nf_ct_expect_related(rtp_exp) != 0)
			continue;
		rtcp_exp->tuple.dst.u.udp.port = htons(port + 1);
		if (nf_ct_expect_related(rtcp_exp) == 0)
			break;
		nf_ct_unexpect_related(rtp_exp);
	}

	if (port == 0)
		goto err1;

	/* Update media port. */
	if (rtp_exp->tuple.dst.u.udp.port != rtp_exp->saved_proto.udp.port &&
	    !ip_nat_sdp_port(skb, dptr, datalen, mediaoff, medialen, port))
		goto err2;

	return NF_ACCEPT;

err2:
	nf_ct_unexpect_related(rtp_exp);
	nf_ct_unexpect_related(rtcp_exp);
err1:
	return NF_DROP;
}