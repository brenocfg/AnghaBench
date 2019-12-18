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
struct cfq_queue {int /*<<< orphan*/  ioprio; TYPE_1__* cfqg; } ;
struct cfq_data {int dummy; } ;
struct TYPE_2__ {int nr_cfqq; } ;

/* Variables and functions */
 int cfq_cfqq_sync (struct cfq_queue*) ; 
 int cfq_prio_slice (struct cfq_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long cfq_slice_offset(struct cfq_data *cfqd,
				      struct cfq_queue *cfqq)
{
	/*
	 * just an approximation, should be ok.
	 */
	return (cfqq->cfqg->nr_cfqq - 1) * (cfq_prio_slice(cfqd, 1, 0) -
		       cfq_prio_slice(cfqd, cfq_cfqq_sync(cfqq), cfqq->ioprio));
}