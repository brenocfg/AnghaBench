#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct rtable {TYPE_2__ u; } ;
struct in_device {int dummy; } ;
struct flowi {scalar_t__ oif; int /*<<< orphan*/  iif; } ;
struct fib_result {TYPE_3__* fi; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int fib_nhs; } ;

/* Variables and functions */
 int __mkroute_input (struct sk_buff*,struct fib_result*,struct in_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtable**) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_select_multipath (struct flowi const*,struct fib_result*) ; 
 int /*<<< orphan*/  rt_genid (int /*<<< orphan*/ ) ; 
 unsigned int rt_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_intern_hash (unsigned int,struct rtable*,int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int ip_mkroute_input(struct sk_buff *skb,
			    struct fib_result *res,
			    const struct flowi *fl,
			    struct in_device *in_dev,
			    __be32 daddr, __be32 saddr, u32 tos)
{
	struct rtable* rth = NULL;
	int err;
	unsigned hash;

#ifdef CONFIG_IP_ROUTE_MULTIPATH
	if (res->fi && res->fi->fib_nhs > 1 && fl->oif == 0)
		fib_select_multipath(fl, res);
#endif

	/* create a routing cache entry */
	err = __mkroute_input(skb, res, in_dev, daddr, saddr, tos, &rth);
	if (err)
		return err;

	/* put it into the cache */
	hash = rt_hash(daddr, saddr, fl->iif,
		       rt_genid(dev_net(rth->u.dst.dev)));
	return rt_intern_hash(hash, rth, NULL, skb);
}