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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  s6_addr; } ;
struct inet6_dev {int /*<<< orphan*/  lock; TYPE_2__ token; int /*<<< orphan*/  cnf; TYPE_1__* nd_parms; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  if_flags; } ;
struct in6_addr {int dummy; } ;
struct ifla_cacheinfo {int /*<<< orphan*/  retrans_time; int /*<<< orphan*/  reachable_time; scalar_t__ tstamp; int /*<<< orphan*/  max_reasm_len; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ci ;
typedef  scalar_t__ __u32 ;
struct TYPE_3__ {int /*<<< orphan*/  retrans_time; int /*<<< orphan*/  reachable_time; } ;

/* Variables and functions */
 int DEVCONF_MAX ; 
 int EMSGSIZE ; 
 int HZ ; 
 int ICMP6_MIB_MAX ; 
 int /*<<< orphan*/  IFLA_INET6_CACHEINFO ; 
 int /*<<< orphan*/  IFLA_INET6_CONF ; 
 int /*<<< orphan*/  IFLA_INET6_FLAGS ; 
 int /*<<< orphan*/  IFLA_INET6_ICMP6STATS ; 
 int /*<<< orphan*/  IFLA_INET6_STATS ; 
 int /*<<< orphan*/  IFLA_INET6_TOKEN ; 
 int /*<<< orphan*/  INITIAL_JIFFIES ; 
 int IPSTATS_MIB_MAX ; 
 int /*<<< orphan*/  IPV6_MAXPLEN ; 
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct ifla_cacheinfo*) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TIME_DELTA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_store_devconf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp6_fill_stats (int /*<<< orphan*/ ,struct inet6_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet6_fill_ifla6_attrs(struct sk_buff *skb, struct inet6_dev *idev)
{
	struct nlattr *nla;
	struct ifla_cacheinfo ci;

	NLA_PUT_U32(skb, IFLA_INET6_FLAGS, idev->if_flags);

	ci.max_reasm_len = IPV6_MAXPLEN;
	ci.tstamp = (__u32)(TIME_DELTA(idev->tstamp, INITIAL_JIFFIES) / HZ * 100
		    + TIME_DELTA(idev->tstamp, INITIAL_JIFFIES) % HZ * 100 / HZ);
	ci.reachable_time = idev->nd_parms->reachable_time;
	ci.retrans_time = idev->nd_parms->retrans_time;
	NLA_PUT(skb, IFLA_INET6_CACHEINFO, sizeof(ci), &ci);

	nla = nla_reserve(skb, IFLA_INET6_CONF, DEVCONF_MAX * sizeof(s32));
	if (nla == NULL)
		goto nla_put_failure;
	ipv6_store_devconf(&idev->cnf, nla_data(nla), nla_len(nla));

	/* XXX - MC not implemented */

	nla = nla_reserve(skb, IFLA_INET6_STATS, IPSTATS_MIB_MAX * sizeof(u64));
	if (nla == NULL)
		goto nla_put_failure;
	snmp6_fill_stats(nla_data(nla), idev, IFLA_INET6_STATS, nla_len(nla));

	nla = nla_reserve(skb, IFLA_INET6_ICMP6STATS, ICMP6_MIB_MAX * sizeof(u64));
	if (nla == NULL)
		goto nla_put_failure;
	snmp6_fill_stats(nla_data(nla), idev, IFLA_INET6_ICMP6STATS, nla_len(nla));

	nla = nla_reserve(skb, IFLA_INET6_TOKEN, sizeof(struct in6_addr));
	if (nla == NULL)
		goto nla_put_failure;
	read_lock_bh(&idev->lock);
	memcpy(nla_data(nla), idev->token.s6_addr, nla_len(nla));
	read_unlock_bh(&idev->lock);

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}