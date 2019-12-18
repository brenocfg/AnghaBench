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
typedef  int /*<<< orphan*/  u32 ;
struct dst_entry {int __use; scalar_t__ dev; int /*<<< orphan*/  metrics; void* output; void* input; int /*<<< orphan*/  __refcnt; } ;
struct TYPE_4__ {struct dst_entry dst; } ;
struct rtable {TYPE_2__ u; TYPE_1__* peer; int /*<<< orphan*/  rt_spec_dst; int /*<<< orphan*/  rt_gateway; int /*<<< orphan*/  rt_iif; int /*<<< orphan*/  rt_src; int /*<<< orphan*/  rt_dst; int /*<<< orphan*/  rt_type; int /*<<< orphan*/  rt_flags; int /*<<< orphan*/  rt_genid; scalar_t__ idev; int /*<<< orphan*/  fl; } ;
struct net {int dummy; } ;
struct flowi {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int RTAX_MAX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_hold (scalar_t__) ; 
 scalar_t__ dst_alloc (int /*<<< orphan*/ *) ; 
 void* dst_discard ; 
 int /*<<< orphan*/  dst_free (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  in_dev_hold (scalar_t__) ; 
 int /*<<< orphan*/  ipv4_dst_blackhole_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt_genid (struct net*) ; 

__attribute__((used)) static int ipv4_dst_blackhole(struct net *net, struct rtable **rp, struct flowi *flp)
{
	struct rtable *ort = *rp;
	struct rtable *rt = (struct rtable *)
		dst_alloc(&ipv4_dst_blackhole_ops);

	if (rt) {
		struct dst_entry *new = &rt->u.dst;

		atomic_set(&new->__refcnt, 1);
		new->__use = 1;
		new->input = dst_discard;
		new->output = dst_discard;
		memcpy(new->metrics, ort->u.dst.metrics, RTAX_MAX*sizeof(u32));

		new->dev = ort->u.dst.dev;
		if (new->dev)
			dev_hold(new->dev);

		rt->fl = ort->fl;

		rt->idev = ort->idev;
		if (rt->idev)
			in_dev_hold(rt->idev);
		rt->rt_genid = rt_genid(net);
		rt->rt_flags = ort->rt_flags;
		rt->rt_type = ort->rt_type;
		rt->rt_dst = ort->rt_dst;
		rt->rt_src = ort->rt_src;
		rt->rt_iif = ort->rt_iif;
		rt->rt_gateway = ort->rt_gateway;
		rt->rt_spec_dst = ort->rt_spec_dst;
		rt->peer = ort->peer;
		if (rt->peer)
			atomic_inc(&rt->peer->refcnt);

		dst_free(new);
	}

	dst_release(&(*rp)->u.dst);
	*rp = rt;
	return (rt ? 0 : -ENOMEM);
}