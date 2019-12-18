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
struct cryptocop_prio_job {int /*<<< orphan*/  node; } ;
struct cryptocop_operation {int /*<<< orphan*/  cb; } ;
typedef  size_t cryptocop_queue_priority ;
struct TYPE_2__ {int /*<<< orphan*/  jobs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_API (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cryptocop_job_queue_lock ; 
 TYPE_1__* cryptocop_job_queues ; 
 int cryptocop_job_setup (struct cryptocop_prio_job**,struct cryptocop_operation*) ; 
 int /*<<< orphan*/  cryptocop_start_job () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cryptocop_job_queue_insert(cryptocop_queue_priority prio, struct cryptocop_operation *operation)
{
	int                           ret;
	struct cryptocop_prio_job     *pj = NULL;
	unsigned long int             flags;

	DEBUG(printk("cryptocop_job_queue_insert(%d, 0x%p)\n", prio, operation));

	if (!operation || !operation->cb){
		DEBUG_API(printk("cryptocop_job_queue_insert oper=0x%p, NULL operation or callback\n", operation));
		return -EINVAL;
	}

	if ((ret = cryptocop_job_setup(&pj, operation)) != 0){
		DEBUG_API(printk("cryptocop_job_queue_insert: job setup failed\n"));
		return ret;
	}
	assert(pj != NULL);

	spin_lock_irqsave(&cryptocop_job_queue_lock, flags);
	list_add_tail(&pj->node, &cryptocop_job_queues[prio].jobs);
	spin_unlock_irqrestore(&cryptocop_job_queue_lock, flags);

	/* Make sure a job is running */
	cryptocop_start_job();
	return 0;
}