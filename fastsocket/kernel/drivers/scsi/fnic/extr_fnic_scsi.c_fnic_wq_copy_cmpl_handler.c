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
struct fnic {unsigned int wq_copy_count; unsigned int raw_wq_count; unsigned int rq_count; int /*<<< orphan*/ * cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  fnic_fcpio_cmpl_handler ; 
 unsigned int vnic_cq_copy_service (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int fnic_wq_copy_cmpl_handler(struct fnic *fnic, int copy_work_to_do)
{
	unsigned int wq_work_done = 0;
	unsigned int i, cq_index;
	unsigned int cur_work_done;

	for (i = 0; i < fnic->wq_copy_count; i++) {
		cq_index = i + fnic->raw_wq_count + fnic->rq_count;
		cur_work_done = vnic_cq_copy_service(&fnic->cq[cq_index],
						     fnic_fcpio_cmpl_handler,
						     copy_work_to_do);
		wq_work_done += cur_work_done;
	}
	return wq_work_done;
}