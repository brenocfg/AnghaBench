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
struct cbq_class {TYPE_2__* q; } ;
struct Qdisc {int dummy; } ;
struct TYPE_3__ {scalar_t__ qlen; } ;
struct TYPE_4__ {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbq_deactivate_class (struct cbq_class*) ; 

__attribute__((used)) static void cbq_qlen_notify(struct Qdisc *sch, unsigned long arg)
{
	struct cbq_class *cl = (struct cbq_class *)arg;

	if (cl->q->q.qlen == 0)
		cbq_deactivate_class(cl);
}