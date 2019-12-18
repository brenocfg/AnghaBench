#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hfsc_class {TYPE_2__* qdisc; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {unsigned int qlen; } ;
struct TYPE_5__ {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  qdisc_tree_decrease_qlen (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static void
hfsc_purge_queue(struct Qdisc *sch, struct hfsc_class *cl)
{
	unsigned int len = cl->qdisc->q.qlen;

	qdisc_reset(cl->qdisc);
	qdisc_tree_decrease_qlen(cl->qdisc, len);
}