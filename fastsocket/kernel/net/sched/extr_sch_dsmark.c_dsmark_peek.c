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
struct sk_buff {int dummy; } ;
struct dsmark_qdisc_data {TYPE_2__* q; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {struct sk_buff* (* peek ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,struct dsmark_qdisc_data*) ; 
 struct dsmark_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 struct sk_buff* stub1 (TYPE_2__*) ; 

__attribute__((used)) static struct sk_buff *dsmark_peek(struct Qdisc *sch)
{
	struct dsmark_qdisc_data *p = qdisc_priv(sch);

	pr_debug("dsmark_peek(sch %p,[qdisc %p])\n", sch, p);

	return p->q->ops->peek(p->q);
}