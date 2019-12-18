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
struct hfsc_class {TYPE_2__* qdisc; } ;
struct Qdisc {int dummy; } ;
struct TYPE_3__ {scalar_t__ qlen; } ;
struct TYPE_4__ {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_passive (struct hfsc_class*) ; 
 int /*<<< orphan*/  update_vf (struct hfsc_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hfsc_qlen_notify(struct Qdisc *sch, unsigned long arg)
{
	struct hfsc_class *cl = (struct hfsc_class *)arg;

	if (cl->qdisc->q.qlen == 0) {
		update_vf(cl, 0, 0);
		set_passive(cl);
	}
}