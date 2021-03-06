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
struct nlattr {int dummy; } ;
struct drr_sched {int /*<<< orphan*/  active; int /*<<< orphan*/  clhash; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int qdisc_class_hash_init (int /*<<< orphan*/ *) ; 
 struct drr_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int drr_init_qdisc(struct Qdisc *sch, struct nlattr *opt)
{
	struct drr_sched *q = qdisc_priv(sch);
	int err;

	err = qdisc_class_hash_init(&q->clhash);
	if (err < 0)
		return err;
	INIT_LIST_HEAD(&q->active);
	return 0;
}