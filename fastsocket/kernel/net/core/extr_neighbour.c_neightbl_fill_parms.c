#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct neigh_parms {int /*<<< orphan*/  locktime; int /*<<< orphan*/  proxy_delay; int /*<<< orphan*/  anycast_delay; int /*<<< orphan*/  retrans_time; int /*<<< orphan*/  delay_probe_time; int /*<<< orphan*/  gc_staletime; int /*<<< orphan*/  base_reachable_time; int /*<<< orphan*/  reachable_time; int /*<<< orphan*/  mcast_probes; int /*<<< orphan*/  ucast_probes; int /*<<< orphan*/  app_probes; int /*<<< orphan*/  proxy_qlen; int /*<<< orphan*/  queue_len; int /*<<< orphan*/  refcnt; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NDTA_PARMS ; 
 int /*<<< orphan*/  NDTPA_ANYCAST_DELAY ; 
 int /*<<< orphan*/  NDTPA_APP_PROBES ; 
 int /*<<< orphan*/  NDTPA_BASE_REACHABLE_TIME ; 
 int /*<<< orphan*/  NDTPA_DELAY_PROBE_TIME ; 
 int /*<<< orphan*/  NDTPA_GC_STALETIME ; 
 int /*<<< orphan*/  NDTPA_IFINDEX ; 
 int /*<<< orphan*/  NDTPA_LOCKTIME ; 
 int /*<<< orphan*/  NDTPA_MCAST_PROBES ; 
 int /*<<< orphan*/  NDTPA_PROXY_DELAY ; 
 int /*<<< orphan*/  NDTPA_PROXY_QLEN ; 
 int /*<<< orphan*/  NDTPA_QUEUE_LEN ; 
 int /*<<< orphan*/  NDTPA_REACHABLE_TIME ; 
 int /*<<< orphan*/  NDTPA_REFCNT ; 
 int /*<<< orphan*/  NDTPA_RETRANS_TIME ; 
 int /*<<< orphan*/  NDTPA_UCAST_PROBES ; 
 int /*<<< orphan*/  NLA_PUT_MSECS (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neightbl_fill_parms(struct sk_buff *skb, struct neigh_parms *parms)
{
	struct nlattr *nest;

	nest = nla_nest_start(skb, NDTA_PARMS);
	if (nest == NULL)
		return -ENOBUFS;

	if (parms->dev)
		NLA_PUT_U32(skb, NDTPA_IFINDEX, parms->dev->ifindex);

	NLA_PUT_U32(skb, NDTPA_REFCNT, atomic_read(&parms->refcnt));
	NLA_PUT_U32(skb, NDTPA_QUEUE_LEN, parms->queue_len);
	NLA_PUT_U32(skb, NDTPA_PROXY_QLEN, parms->proxy_qlen);
	NLA_PUT_U32(skb, NDTPA_APP_PROBES, parms->app_probes);
	NLA_PUT_U32(skb, NDTPA_UCAST_PROBES, parms->ucast_probes);
	NLA_PUT_U32(skb, NDTPA_MCAST_PROBES, parms->mcast_probes);
	NLA_PUT_MSECS(skb, NDTPA_REACHABLE_TIME, parms->reachable_time);
	NLA_PUT_MSECS(skb, NDTPA_BASE_REACHABLE_TIME,
		      parms->base_reachable_time);
	NLA_PUT_MSECS(skb, NDTPA_GC_STALETIME, parms->gc_staletime);
	NLA_PUT_MSECS(skb, NDTPA_DELAY_PROBE_TIME, parms->delay_probe_time);
	NLA_PUT_MSECS(skb, NDTPA_RETRANS_TIME, parms->retrans_time);
	NLA_PUT_MSECS(skb, NDTPA_ANYCAST_DELAY, parms->anycast_delay);
	NLA_PUT_MSECS(skb, NDTPA_PROXY_DELAY, parms->proxy_delay);
	NLA_PUT_MSECS(skb, NDTPA_LOCKTIME, parms->locktime);

	return nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -EMSGSIZE;
}