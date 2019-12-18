#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cryptocop_prio_job {int /*<<< orphan*/  node; int /*<<< orphan*/  iop; TYPE_2__* oper; } ;
struct TYPE_4__ {int data; } ;
typedef  TYPE_1__ reg_dma_rw_ack_intr ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* cb ) (TYPE_2__*,int /*<<< orphan*/ ) ;scalar_t__ fast_callback; scalar_t__ operation_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_DMA_INST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  cryptocop_completed_jobs ; 
 int /*<<< orphan*/  cryptocop_completed_jobs_lock ; 
 int /*<<< orphan*/  cryptocop_process_lock ; 
 struct cryptocop_prio_job* cryptocop_running_job ; 
 int /*<<< orphan*/  cryptocop_start_job () ; 
 int /*<<< orphan*/  cryptocop_tasklet ; 
 int /*<<< orphan*/  delete_internal_operation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  kfree (struct cryptocop_prio_job*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  running_job_lock ; 
 int /*<<< orphan*/  rw_ack_intr ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
dma_done_interrupt(int irq, void *dev_id)
{
	struct cryptocop_prio_job *done_job;
	reg_dma_rw_ack_intr ack_intr = {
		.data = 1,
	};

	REG_WR(dma, IN_DMA_INST, rw_ack_intr, ack_intr);

	DEBUG(printk("cryptocop DMA done\n"));

	spin_lock(&running_job_lock);
	if (cryptocop_running_job == NULL){
		printk("stream co-processor got interrupt when not busy\n");
		spin_unlock(&running_job_lock);
		return IRQ_HANDLED;
	}
	done_job = cryptocop_running_job;
	cryptocop_running_job = NULL;
	spin_unlock(&running_job_lock);

	/* Start processing a job. */
	if (!spin_trylock(&cryptocop_process_lock)){
		DEBUG(printk("cryptocop irq handler, not starting a job\n"));
	} else {
		cryptocop_start_job();
		spin_unlock(&cryptocop_process_lock);
	}

	done_job->oper->operation_status = 0; /* Job is completed. */
	if (done_job->oper->fast_callback){
		/* This operation wants callback from interrupt. */
		done_job->oper->cb(done_job->oper, done_job->oper->cb_data);
		delete_internal_operation(done_job->iop);
		kfree(done_job);
	} else {
		spin_lock(&cryptocop_completed_jobs_lock);
		list_add_tail(&(done_job->node), &cryptocop_completed_jobs);
		spin_unlock(&cryptocop_completed_jobs_lock);
		tasklet_schedule(&cryptocop_tasklet);
	}

	DEBUG(printk("cryptocop leave irq handler\n"));
	return IRQ_HANDLED;
}