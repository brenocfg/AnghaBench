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
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct Qdisc_ops {scalar_t__ (* init ) (struct Qdisc*,int /*<<< orphan*/ *) ;} ;
struct Qdisc {unsigned int parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct Qdisc*) ; 
 struct Qdisc* qdisc_alloc (struct netdev_queue*,struct Qdisc_ops*) ; 
 int /*<<< orphan*/  qdisc_destroy (struct Qdisc*) ; 
 scalar_t__ stub1 (struct Qdisc*,int /*<<< orphan*/ *) ; 

struct Qdisc * qdisc_create_dflt(struct net_device *dev,
				 struct netdev_queue *dev_queue,
				 struct Qdisc_ops *ops,
				 unsigned int parentid)
{
	struct Qdisc *sch;

	sch = qdisc_alloc(dev_queue, ops);
	if (IS_ERR(sch))
		goto errout;
	sch->parent = parentid;

	if (!ops->init || ops->init(sch, NULL) == 0)
		return sch;

	qdisc_destroy(sch);
errout:
	return NULL;
}