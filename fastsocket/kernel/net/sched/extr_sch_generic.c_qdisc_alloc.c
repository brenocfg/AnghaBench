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
struct Qdisc_ops {int priv_size; int /*<<< orphan*/  dequeue; int /*<<< orphan*/  enqueue; } ;
struct Qdisc {int padded; int /*<<< orphan*/  refcnt; struct netdev_queue* dev_queue; int /*<<< orphan*/  dequeue; int /*<<< orphan*/  enqueue; struct Qdisc_ops* ops; int /*<<< orphan*/  q; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOBUFS ; 
 struct Qdisc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int QDISC_ALIGN (unsigned long) ; 
 int QDISC_ALIGNTO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 void* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

struct Qdisc *qdisc_alloc(struct netdev_queue *dev_queue,
			  struct Qdisc_ops *ops)
{
	void *p;
	struct Qdisc *sch;
	unsigned int size;
	int err = -ENOBUFS;

	/* ensure that the Qdisc and the private data are 32-byte aligned */
	size = QDISC_ALIGN(sizeof(*sch));
	size += ops->priv_size + (QDISC_ALIGNTO - 1);

	p = kzalloc(size, GFP_KERNEL);
	if (!p)
		goto errout;
	sch = (struct Qdisc *) QDISC_ALIGN((unsigned long) p);
	sch->padded = (char *) sch - (char *) p;

	INIT_LIST_HEAD(&sch->list);
	skb_queue_head_init(&sch->q);
	sch->ops = ops;
	sch->enqueue = ops->enqueue;
	sch->dequeue = ops->dequeue;
	sch->dev_queue = dev_queue;
	dev_hold(qdisc_dev(sch));
	atomic_set(&sch->refcnt, 1);

	return sch;
errout:
	return ERR_PTR(err);
}