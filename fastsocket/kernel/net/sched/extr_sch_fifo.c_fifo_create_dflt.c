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
struct Qdisc_ops {int dummy; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct Qdisc* ERR_PTR (int) ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int) ; 
 int fifo_set_limit (struct Qdisc*,unsigned int) ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct Qdisc_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_destroy (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 

struct Qdisc *fifo_create_dflt(struct Qdisc *sch, struct Qdisc_ops *ops,
			       unsigned int limit)
{
	struct Qdisc *q;
	int err = -ENOMEM;

	q = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
			      ops, TC_H_MAKE(sch->handle, 1));
	if (q) {
		err = fifo_set_limit(q, limit);
		if (err < 0) {
			qdisc_destroy(q);
			q = NULL;
		}
	}

	return q ? : ERR_PTR(err);
}