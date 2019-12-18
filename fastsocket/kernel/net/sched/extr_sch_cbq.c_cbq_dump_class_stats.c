#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gnet_dump {int dummy; } ;
struct cbq_sched_data {scalar_t__ now; } ;
struct TYPE_8__ {scalar_t__ undertime; int /*<<< orphan*/  avgidle; } ;
struct TYPE_7__ {int /*<<< orphan*/  qlen; } ;
struct cbq_class {scalar_t__ undertime; TYPE_4__ xstats; TYPE_3__ qstats; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; int /*<<< orphan*/  avgidle; TYPE_2__* q; } ;
struct Qdisc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_6__ {TYPE_1__ q; } ;

/* Variables and functions */
 scalar_t__ PSCHED_PASTPERFECT ; 
 int gnet_stats_copy_app (struct gnet_dump*,TYPE_4__*,int) ; 
 scalar_t__ gnet_stats_copy_basic (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,TYPE_3__*) ; 
 scalar_t__ gnet_stats_copy_rate_est (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 struct cbq_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int
cbq_dump_class_stats(struct Qdisc *sch, unsigned long arg,
	struct gnet_dump *d)
{
	struct cbq_sched_data *q = qdisc_priv(sch);
	struct cbq_class *cl = (struct cbq_class*)arg;

	cl->qstats.qlen = cl->q->q.qlen;
	cl->xstats.avgidle = cl->avgidle;
	cl->xstats.undertime = 0;

	if (cl->undertime != PSCHED_PASTPERFECT)
		cl->xstats.undertime = cl->undertime - q->now;

	if (gnet_stats_copy_basic(d, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, &cl->qstats) < 0)
		return -1;

	return gnet_stats_copy_app(d, &cl->xstats, sizeof(cl->xstats));
}