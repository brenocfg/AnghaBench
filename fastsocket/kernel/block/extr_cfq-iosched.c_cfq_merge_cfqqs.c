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
struct cfq_queue {int /*<<< orphan*/  new_cfqq; } ;
struct cfq_io_context {int dummy; } ;
struct cfq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_coop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_put_queue (struct cfq_queue*) ; 
 int /*<<< orphan*/  cic_set_cfqq (struct cfq_io_context*,int /*<<< orphan*/ ,int) ; 
 struct cfq_queue* cic_to_cfqq (struct cfq_io_context*,int) ; 

__attribute__((used)) static struct cfq_queue *
cfq_merge_cfqqs(struct cfq_data *cfqd, struct cfq_io_context *cic,
		struct cfq_queue *cfqq)
{
	cfq_log_cfqq(cfqd, cfqq, "merging with queue %p", cfqq->new_cfqq);
	cic_set_cfqq(cic, cfqq->new_cfqq, 1);
	cfq_mark_cfqq_coop(cfqq->new_cfqq);
	cfq_put_queue(cfqq);
	return cic_to_cfqq(cic, 1);
}