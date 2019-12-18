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
struct cfq_queue {int dummy; } ;
struct cfq_data {int /*<<< orphan*/  busy_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_resort_rr_list (struct cfq_data*,struct cfq_queue*) ; 

__attribute__((used)) static void cfq_add_cfqq_rr(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	cfq_log_cfqq(cfqd, cfqq, "add_to_rr");
	BUG_ON(cfq_cfqq_on_rr(cfqq));
	cfq_mark_cfqq_on_rr(cfqq);
	cfqd->busy_queues++;

	cfq_resort_rr_list(cfqd, cfqq);
}