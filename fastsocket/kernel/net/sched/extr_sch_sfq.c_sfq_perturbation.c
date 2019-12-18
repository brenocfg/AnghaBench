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
struct sfq_sched_data {scalar_t__ perturb_period; int /*<<< orphan*/  perturb_timer; int /*<<< orphan*/  perturbation; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  net_random () ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void sfq_perturbation(unsigned long arg)
{
	struct Qdisc *sch = (struct Qdisc *)arg;
	struct sfq_sched_data *q = qdisc_priv(sch);

	q->perturbation = net_random();

	if (q->perturb_period)
		mod_timer(&q->perturb_timer, jiffies + q->perturb_period);
}