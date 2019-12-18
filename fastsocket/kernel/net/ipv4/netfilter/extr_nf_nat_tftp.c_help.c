#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  port; } ;
struct TYPE_9__ {TYPE_1__ udp; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  expectfn; int /*<<< orphan*/  dir; TYPE_2__ saved_proto; struct nf_conn* master; } ;
struct nf_conn {TYPE_7__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_10__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {TYPE_3__ udp; } ;
struct TYPE_12__ {TYPE_4__ u; } ;
struct TYPE_13__ {TYPE_5__ src; } ;
struct TYPE_14__ {TYPE_6__ tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  IP_CT_DIR_REPLY ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_nat_follow_master ; 

__attribute__((used)) static unsigned int help(struct sk_buff *skb,
			 enum ip_conntrack_info ctinfo,
			 struct nf_conntrack_expect *exp)
{
	const struct nf_conn *ct = exp->master;

	exp->saved_proto.udp.port
		= ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.udp.port;
	exp->dir = IP_CT_DIR_REPLY;
	exp->expectfn = nf_nat_follow_master;
	if (nf_ct_expect_related(exp) != 0)
		return NF_DROP;
	return NF_ACCEPT;
}