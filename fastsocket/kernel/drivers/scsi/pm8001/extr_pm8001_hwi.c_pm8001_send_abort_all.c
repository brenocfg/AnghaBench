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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  task_abort ;
struct task_abort_req {void* tag; void* device_id; void* abort_all; } ;
struct sas_task {int /*<<< orphan*/  task_done; } ;
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {size_t device_id; } ;
struct pm8001_ccb_info {size_t ccb_tag; struct sas_task* task; struct pm8001_device* device; } ;
struct inbound_queue_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t OPC_INB_SATA_ABORT ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  memset (struct task_abort_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,size_t,struct task_abort_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,size_t*) ; 
 int /*<<< orphan*/  pm8001_task_done ; 
 struct sas_task* sas_alloc_slow_task (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm8001_send_abort_all(struct pm8001_hba_info *pm8001_ha,
		struct pm8001_device *pm8001_ha_dev)
{
	int res;
	u32 ccb_tag;
	struct pm8001_ccb_info *ccb;
	struct sas_task *task = NULL;
	struct task_abort_req task_abort;
	struct inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SATA_ABORT;
	int ret;

	if (!pm8001_ha_dev) {
		PM8001_FAIL_DBG(pm8001_ha, pm8001_printk("dev is null\n"));
		return;
	}

	task = sas_alloc_slow_task(GFP_ATOMIC);

	if (!task) {
		PM8001_FAIL_DBG(pm8001_ha, pm8001_printk("cannot "
						"allocate task\n"));
		return;
	}

	task->task_done = pm8001_task_done;

	res = pm8001_tag_alloc(pm8001_ha, &ccb_tag);
	if (res)
		return;

	ccb = &pm8001_ha->ccb_info[ccb_tag];
	ccb->device = pm8001_ha_dev;
	ccb->ccb_tag = ccb_tag;
	ccb->task = task;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	memset(&task_abort, 0, sizeof(task_abort));
	task_abort.abort_all = cpu_to_le32(1);
	task_abort.device_id = cpu_to_le32(pm8001_ha_dev->device_id);
	task_abort.tag = cpu_to_le32(ccb_tag);

	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &task_abort, 0);

}