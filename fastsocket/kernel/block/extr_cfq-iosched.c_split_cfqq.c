#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cfq_queue {int /*<<< orphan*/  pid; } ;
struct cfq_io_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_clear_cfqq_coop (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_split_coop (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_put_queue (struct cfq_queue*) ; 
 int cfqq_process_refs (struct cfq_queue*) ; 
 int /*<<< orphan*/  cic_set_cfqq (struct cfq_io_context*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* current ; 

__attribute__((used)) static struct cfq_queue *
split_cfqq(struct cfq_io_context *cic, struct cfq_queue *cfqq)
{
	if (cfqq_process_refs(cfqq) == 1) {
		cfqq->pid = current->pid;
		cfq_clear_cfqq_coop(cfqq);
		cfq_clear_cfqq_split_coop(cfqq);
		return cfqq;
	}

	cic_set_cfqq(cic, NULL, 1);
	cfq_put_queue(cfqq);
	return NULL;
}