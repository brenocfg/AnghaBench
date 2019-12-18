#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rtable {int dummy; } ;
struct net_device {int dummy; } ;
struct flowi {int /*<<< orphan*/  oif; int /*<<< orphan*/  fl4_src; int /*<<< orphan*/  fl4_dst; } ;
struct fib_result {int dummy; } ;

/* Variables and functions */
 int __mkroute_output (struct rtable**,struct fib_result*,struct flowi const*,struct flowi const*,struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  rt_genid (int /*<<< orphan*/ ) ; 
 unsigned int rt_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_intern_hash (unsigned int,struct rtable*,struct rtable**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip_mkroute_output(struct rtable **rp,
			     struct fib_result *res,
			     const struct flowi *fl,
			     const struct flowi *oldflp,
			     struct net_device *dev_out,
			     unsigned flags)
{
	struct rtable *rth = NULL;
	int err = __mkroute_output(&rth, res, fl, oldflp, dev_out, flags);
	unsigned hash;
	if (err == 0) {
		hash = rt_hash(oldflp->fl4_dst, oldflp->fl4_src, oldflp->oif,
			       rt_genid(dev_net(dev_out)));
		err = rt_intern_hash(hash, rth, rp, NULL);
	}

	return err;
}