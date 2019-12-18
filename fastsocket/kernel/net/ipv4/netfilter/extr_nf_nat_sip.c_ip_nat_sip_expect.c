#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct sk_buff {int dummy; } ;
struct TYPE_24__ {scalar_t__ port; } ;
struct TYPE_25__ {TYPE_16__ udp; } ;
struct TYPE_20__ {scalar_t__ port; } ;
struct TYPE_21__ {TYPE_12__ udp; } ;
struct TYPE_19__ {scalar_t__ ip; } ;
struct TYPE_22__ {TYPE_13__ u; TYPE_11__ u3; } ;
struct TYPE_23__ {TYPE_14__ dst; } ;
struct nf_conntrack_expect {scalar_t__ saved_ip; int dir; TYPE_17__ saved_proto; TYPE_15__ tuple; int /*<<< orphan*/  expectfn; } ;
struct nf_conn {TYPE_10__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  scalar_t__ __be32 ;
struct TYPE_31__ {scalar_t__ port; } ;
struct TYPE_32__ {TYPE_6__ udp; } ;
struct TYPE_27__ {scalar_t__ ip; } ;
struct TYPE_33__ {TYPE_7__ u; TYPE_2__ u3; } ;
struct TYPE_28__ {scalar_t__ port; } ;
struct TYPE_29__ {TYPE_3__ udp; } ;
struct TYPE_26__ {scalar_t__ ip; } ;
struct TYPE_30__ {TYPE_4__ u; TYPE_1__ u3; } ;
struct TYPE_34__ {TYPE_8__ dst; TYPE_5__ src; } ;
struct TYPE_18__ {TYPE_9__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  ip_nat_sip_expected ; 
 int /*<<< orphan*/  mangle_packet (struct sk_buff*,char const**,unsigned int*,unsigned int,unsigned int,char*,unsigned int) ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 unsigned int sprintf (char*,char*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static unsigned int ip_nat_sip_expect(struct sk_buff *skb,
				      const char **dptr, unsigned int *datalen,
				      struct nf_conntrack_expect *exp,
				      unsigned int matchoff,
				      unsigned int matchlen)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	__be32 newip;
	u_int16_t port;
	char buffer[sizeof("nnn.nnn.nnn.nnn:nnnnn")];
	unsigned buflen;

	/* Connection will come from reply */
	if (ct->tuplehash[dir].tuple.src.u3.ip == ct->tuplehash[!dir].tuple.dst.u3.ip)
		newip = exp->tuple.dst.u3.ip;
	else
		newip = ct->tuplehash[!dir].tuple.dst.u3.ip;

	/* If the signalling port matches the connection's source port in the
	 * original direction, try to use the destination port in the opposite
	 * direction. */
	if (exp->tuple.dst.u.udp.port ==
	    ct->tuplehash[dir].tuple.src.u.udp.port)
		port = ntohs(ct->tuplehash[!dir].tuple.dst.u.udp.port);
	else
		port = ntohs(exp->tuple.dst.u.udp.port);

	exp->saved_ip = exp->tuple.dst.u3.ip;
	exp->tuple.dst.u3.ip = newip;
	exp->saved_proto.udp.port = exp->tuple.dst.u.udp.port;
	exp->dir = !dir;
	exp->expectfn = ip_nat_sip_expected;

	for (; port != 0; port++) {
		exp->tuple.dst.u.udp.port = htons(port);
		if (nf_ct_expect_related(exp) == 0)
			break;
	}

	if (port == 0)
		return NF_DROP;

	if (exp->tuple.dst.u3.ip != exp->saved_ip ||
	    exp->tuple.dst.u.udp.port != exp->saved_proto.udp.port) {
		buflen = sprintf(buffer, "%pI4:%u", &newip, port);
		if (!mangle_packet(skb, dptr, datalen, matchoff, matchlen,
				   buffer, buflen))
			goto err;
	}
	return NF_ACCEPT;

err:
	nf_ct_unexpect_related(exp);
	return NF_DROP;
}