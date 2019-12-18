#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tc_fifo_qopt {int limit; } ;
struct nlattr {int dummy; } ;
struct fifo_sched_data {int limit; } ;
struct Qdisc {int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {scalar_t__ tx_queue_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bfifo_qdisc_ops ; 
 struct tc_fifo_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int psched_mtu (TYPE_1__*) ; 
 TYPE_1__* qdisc_dev (struct Qdisc*) ; 
 struct fifo_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int fifo_init(struct Qdisc *sch, struct nlattr *opt)
{
	struct fifo_sched_data *q = qdisc_priv(sch);

	if (opt == NULL) {
		u32 limit = qdisc_dev(sch)->tx_queue_len ? : 1;

		if (sch->ops == &bfifo_qdisc_ops)
			limit *= psched_mtu(qdisc_dev(sch));

		q->limit = limit;
	} else {
		struct tc_fifo_qopt *ctl = nla_data(opt);

		if (nla_len(opt) < sizeof(*ctl))
			return -EINVAL;

		q->limit = ctl->limit;
	}

	return 0;
}