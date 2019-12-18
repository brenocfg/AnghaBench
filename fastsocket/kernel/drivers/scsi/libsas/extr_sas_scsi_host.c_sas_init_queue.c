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
struct scsi_core {int /*<<< orphan*/  queue_thread; TYPE_1__* shost; int /*<<< orphan*/  task_queue; scalar_t__ task_queue_size; int /*<<< orphan*/  task_queue_flush; int /*<<< orphan*/  task_queue_lock; } ;
struct sas_ha_struct {struct scsi_core core; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct sas_ha_struct*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_queue_thread ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int sas_init_queue(struct sas_ha_struct *sas_ha)
{
	struct scsi_core *core = &sas_ha->core;

	spin_lock_init(&core->task_queue_lock);
	mutex_init(&core->task_queue_flush);
	core->task_queue_size = 0;
	INIT_LIST_HEAD(&core->task_queue);

	core->queue_thread = kthread_run(sas_queue_thread, sas_ha,
					 "sas_queue_%d", core->shost->host_no);
	if (IS_ERR(core->queue_thread))
		return PTR_ERR(core->queue_thread);
	return 0;
}