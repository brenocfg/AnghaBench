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
struct tc_fifo_qopt {int /*<<< orphan*/  limit; } ;
struct nlattr {int dummy; } ;
struct fifo_sched_data {int /*<<< orphan*/  oldest; int /*<<< orphan*/  limit; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_queue_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PSCHED_PASTPERFECT ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tc_fifo_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 TYPE_1__* qdisc_dev (struct Qdisc*) ; 
 struct fifo_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int tfifo_init(struct Qdisc *sch, struct nlattr *opt)
{
	struct fifo_sched_data *q = qdisc_priv(sch);

	if (opt) {
		struct tc_fifo_qopt *ctl = nla_data(opt);
		if (nla_len(opt) < sizeof(*ctl))
			return -EINVAL;

		q->limit = ctl->limit;
	} else
		q->limit = max_t(u32, qdisc_dev(sch)->tx_queue_len, 1);

	q->oldest = PSCHED_PASTPERFECT;
	return 0;
}