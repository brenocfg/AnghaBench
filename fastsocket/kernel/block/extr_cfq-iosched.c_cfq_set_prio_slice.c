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
struct cfq_queue {void* slice_end; unsigned int allocated_slice; void* slice_start; int /*<<< orphan*/  cfqg; } ;
struct cfq_data {unsigned int* cfq_slice; int cfq_slice_idle; scalar_t__ cfq_latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_class_rt (struct cfq_queue*) ; 
 unsigned int cfq_group_get_avg_queues (struct cfq_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int cfq_group_slice (struct cfq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,void*) ; 
 unsigned int cfq_prio_to_slice (struct cfq_data*,struct cfq_queue*) ; 
 void* jiffies ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static inline void
cfq_set_prio_slice(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	unsigned slice = cfq_prio_to_slice(cfqd, cfqq);
	if (cfqd->cfq_latency) {
		/*
		 * interested queues (we consider only the ones with the same
		 * priority class in the cfq group)
		 */
		unsigned iq = cfq_group_get_avg_queues(cfqd, cfqq->cfqg,
						cfq_class_rt(cfqq));
		unsigned sync_slice = cfqd->cfq_slice[1];
		unsigned expect_latency = sync_slice * iq;
		unsigned group_slice = cfq_group_slice(cfqd, cfqq->cfqg);

		if (expect_latency > group_slice) {
			unsigned base_low_slice = 2 * cfqd->cfq_slice_idle;
			/* scale low_slice according to IO priority
			 * and sync vs async */
			unsigned low_slice =
				min(slice, base_low_slice * slice / sync_slice);
			/* the adapted slice value is scaled to fit all iqs
			 * into the target latency */
			slice = max(slice * group_slice / expect_latency,
				    low_slice);
		}
	}
	cfqq->slice_start = jiffies;
	cfqq->slice_end = jiffies + slice;
	cfqq->allocated_slice = slice;
	cfq_log_cfqq(cfqd, cfqq, "set_slice=%lu", cfqq->slice_end - jiffies);
}