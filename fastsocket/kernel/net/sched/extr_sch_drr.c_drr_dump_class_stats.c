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
typedef  int /*<<< orphan*/  xstats ;
struct tc_drr_stats {int /*<<< orphan*/  deficit; } ;
struct gnet_dump {int dummy; } ;
struct drr_class {TYPE_2__* qdisc; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; int /*<<< orphan*/  deficit; } ;
struct Qdisc {int dummy; } ;
struct TYPE_6__ {scalar_t__ qlen; } ;
struct TYPE_4__ {scalar_t__ qlen; } ;
struct TYPE_5__ {TYPE_3__ qstats; TYPE_1__ q; } ;

/* Variables and functions */
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_drr_stats*,int) ; 
 scalar_t__ gnet_stats_copy_basic (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,TYPE_3__*) ; 
 scalar_t__ gnet_stats_copy_rate_est (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tc_drr_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int drr_dump_class_stats(struct Qdisc *sch, unsigned long arg,
				struct gnet_dump *d)
{
	struct drr_class *cl = (struct drr_class *)arg;
	struct tc_drr_stats xstats;

	memset(&xstats, 0, sizeof(xstats));
	if (cl->qdisc->q.qlen) {
		xstats.deficit = cl->deficit;
		cl->qdisc->qstats.qlen = cl->qdisc->q.qlen;
	}

	if (gnet_stats_copy_basic(d, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, &cl->qdisc->qstats) < 0)
		return -1;

	return gnet_stats_copy_app(d, &xstats, sizeof(xstats));
}