#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct sk_buff {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  port; } ;
struct TYPE_18__ {TYPE_11__ tcp; } ;
struct TYPE_16__ {int /*<<< orphan*/  ip; } ;
struct TYPE_19__ {TYPE_12__ u; TYPE_10__ u3; } ;
struct TYPE_28__ {int /*<<< orphan*/  port; } ;
struct TYPE_29__ {TYPE_7__ tcp; } ;
struct TYPE_27__ {int /*<<< orphan*/  ip; } ;
struct TYPE_30__ {TYPE_8__ u; TYPE_6__ u3; } ;
struct TYPE_20__ {TYPE_13__ dst; TYPE_9__ src; } ;
struct TYPE_22__ {int /*<<< orphan*/  port; } ;
struct TYPE_23__ {TYPE_1__ tcp; } ;
struct nf_conntrack_expect {int dir; TYPE_14__ tuple; int /*<<< orphan*/  expectfn; TYPE_2__ saved_proto; int /*<<< orphan*/  saved_ip; } ;
struct nf_conn {TYPE_5__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  __be16 ;
typedef  int /*<<< orphan*/  TransportAddress ;
struct TYPE_21__ {int /*<<< orphan*/  ip; } ;
struct TYPE_24__ {TYPE_15__ u3; } ;
struct TYPE_25__ {TYPE_3__ dst; } ;
struct TYPE_26__ {TYPE_4__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  ip_nat_callforwarding_expect ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  set_h225_addr (struct sk_buff*,unsigned char**,int,int /*<<< orphan*/ *,TYPE_15__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nat_callforwarding(struct sk_buff *skb, struct nf_conn *ct,
			      enum ip_conntrack_info ctinfo,
			      unsigned char **data, int dataoff,
			      TransportAddress *taddr, __be16 port,
			      struct nf_conntrack_expect *exp)
{
	int dir = CTINFO2DIR(ctinfo);
	u_int16_t nated_port;

	/* Set expectations for NAT */
	exp->saved_ip = exp->tuple.dst.u3.ip;
	exp->tuple.dst.u3.ip = ct->tuplehash[!dir].tuple.dst.u3.ip;
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->expectfn = ip_nat_callforwarding_expect;
	exp->dir = !dir;

	/* Try to get same port: if not, try to change it. */
	for (nated_port = ntohs(port); nated_port != 0; nated_port++) {
		exp->tuple.dst.u.tcp.port = htons(nated_port);
		if (nf_ct_expect_related(exp) == 0)
			break;
	}

	if (nated_port == 0) {	/* No port available */
		if (net_ratelimit())
			printk("nf_nat_q931: out of TCP ports\n");
		return 0;
	}

	/* Modify signal */
	if (!set_h225_addr(skb, data, dataoff, taddr,
			   &ct->tuplehash[!dir].tuple.dst.u3,
			   htons(nated_port)) == 0) {
		nf_ct_unexpect_related(exp);
		return -1;
	}

	/* Success */
	pr_debug("nf_nat_q931: expect Call Forwarding %pI4:%hu->%pI4:%hu\n",
		 &exp->tuple.src.u3.ip,
		 ntohs(exp->tuple.src.u.tcp.port),
		 &exp->tuple.dst.u3.ip,
		 ntohs(exp->tuple.dst.u.tcp.port));

	return 0;
}