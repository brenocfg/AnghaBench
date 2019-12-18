#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;
struct sk_buff {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  port; } ;
struct TYPE_17__ {TYPE_3__ tcp; } ;
struct TYPE_18__ {TYPE_4__ u; } ;
struct TYPE_19__ {TYPE_5__ dst; } ;
struct TYPE_14__ {int /*<<< orphan*/  port; } ;
struct TYPE_15__ {TYPE_1__ tcp; } ;
struct nf_conntrack_expect {size_t dir; TYPE_11__* master; TYPE_6__ tuple; TYPE_2__ saved_proto; int /*<<< orphan*/  expectfn; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_20__ {int /*<<< orphan*/  ip; } ;
struct TYPE_21__ {TYPE_7__ u3; } ;
struct TYPE_22__ {TYPE_8__ dst; } ;
struct TYPE_13__ {TYPE_10__* tuplehash; } ;
struct TYPE_12__ {TYPE_9__ tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_REPLY ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_unexpect_related (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_nat_follow_master ; 
 unsigned int nf_nat_mangle_tcp_packet (struct sk_buff*,TYPE_11__*,int,unsigned int,unsigned int,char*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static unsigned int help(struct sk_buff *skb,
			 enum ip_conntrack_info ctinfo,
			 unsigned int matchoff,
			 unsigned int matchlen,
			 struct nf_conntrack_expect *exp)
{
	char buffer[sizeof("4294967296 65635")];
	u_int32_t ip;
	u_int16_t port;
	unsigned int ret;

	/* Reply comes from server. */
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->dir = IP_CT_DIR_REPLY;
	exp->expectfn = nf_nat_follow_master;

	/* Try to get same port: if not, try to change it. */
	for (port = ntohs(exp->saved_proto.tcp.port); port != 0; port++) {
		exp->tuple.dst.u.tcp.port = htons(port);
		if (nf_ct_expect_related(exp) == 0)
			break;
	}

	if (port == 0)
		return NF_DROP;

	ip = ntohl(exp->master->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip);
	sprintf(buffer, "%u %u", ip, port);
	pr_debug("nf_nat_irc: inserting '%s' == %pI4, port %u\n",
		 buffer, &ip, port);

	ret = nf_nat_mangle_tcp_packet(skb, exp->master, ctinfo,
				       matchoff, matchlen, buffer,
				       strlen(buffer));
	if (ret != NF_ACCEPT)
		nf_ct_unexpect_related(exp);
	return ret;
}