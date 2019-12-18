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
union nf_inet_addr {scalar_t__ ip; } ;
struct sk_buff {int dummy; } ;
struct nf_ct_h323_master {scalar_t__* sig_port; } ;
struct nf_conn {TYPE_5__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  scalar_t__ __be16 ;
typedef  int /*<<< orphan*/  TransportAddress ;
struct TYPE_8__ {struct nf_ct_h323_master ct_h323_info; } ;
struct TYPE_14__ {TYPE_1__ help; } ;
struct TYPE_13__ {scalar_t__ ip; } ;
struct TYPE_10__ {TYPE_6__ u3; } ;
struct TYPE_9__ {TYPE_6__ u3; } ;
struct TYPE_11__ {TYPE_3__ src; TYPE_2__ dst; } ;
struct TYPE_12__ {TYPE_4__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 scalar_t__ get_h225_addr (struct nf_conn*,unsigned char*,int /*<<< orphan*/ *,union nf_inet_addr*,scalar_t__*) ; 
 TYPE_7__* nfct_help (struct nf_conn*) ; 
 int ntohl (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__*,scalar_t__,scalar_t__*,scalar_t__) ; 
 int set_h225_addr (struct sk_buff*,unsigned char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*,scalar_t__) ; 

__attribute__((used)) static int set_sig_addr(struct sk_buff *skb, struct nf_conn *ct,
			enum ip_conntrack_info ctinfo,
			unsigned char **data,
			TransportAddress *taddr, int count)
{
	const struct nf_ct_h323_master *info = &nfct_help(ct)->help.ct_h323_info;
	int dir = CTINFO2DIR(ctinfo);
	int i;
	__be16 port;
	union nf_inet_addr addr;

	for (i = 0; i < count; i++) {
		if (get_h225_addr(ct, *data, &taddr[i], &addr, &port)) {
			if (addr.ip == ct->tuplehash[dir].tuple.src.u3.ip &&
			    port == info->sig_port[dir]) {
				/* GW->GK */

				/* Fix for Gnomemeeting */
				if (i > 0 &&
				    get_h225_addr(ct, *data, &taddr[0],
						  &addr, &port) &&
				    (ntohl(addr.ip) & 0xff000000) == 0x7f000000)
					i = 0;

				pr_debug("nf_nat_ras: set signal address %pI4:%hu->%pI4:%hu\n",
					 &addr.ip, port,
					 &ct->tuplehash[!dir].tuple.dst.u3.ip,
					 info->sig_port[!dir]);
				return set_h225_addr(skb, data, 0, &taddr[i],
						     &ct->tuplehash[!dir].
						     tuple.dst.u3,
						     info->sig_port[!dir]);
			} else if (addr.ip == ct->tuplehash[dir].tuple.dst.u3.ip &&
				   port == info->sig_port[dir]) {
				/* GK->GW */
				pr_debug("nf_nat_ras: set signal address %pI4:%hu->%pI4:%hu\n",
					 &addr.ip, port,
					 &ct->tuplehash[!dir].tuple.src.u3.ip,
					 info->sig_port[!dir]);
				return set_h225_addr(skb, data, 0, &taddr[i],
						     &ct->tuplehash[!dir].
						     tuple.src.u3,
						     info->sig_port[!dir]);
			}
		}
	}

	return 0;
}