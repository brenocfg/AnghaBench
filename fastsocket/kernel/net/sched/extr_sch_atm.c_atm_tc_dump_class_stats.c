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
struct gnet_dump {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  qlen; } ;
struct atm_flow_data {TYPE_3__ qstats; int /*<<< orphan*/  bstats; TYPE_2__* q; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_5__ {TYPE_1__ q; } ;

/* Variables and functions */
 scalar_t__ gnet_stats_copy_basic (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,TYPE_3__*) ; 

__attribute__((used)) static int
atm_tc_dump_class_stats(struct Qdisc *sch, unsigned long arg,
			struct gnet_dump *d)
{
	struct atm_flow_data *flow = (struct atm_flow_data *)arg;

	flow->qstats.qlen = flow->q->q.qlen;

	if (gnet_stats_copy_basic(d, &flow->bstats) < 0 ||
	    gnet_stats_copy_queue(d, &flow->qstats) < 0)
		return -1;

	return 0;
}