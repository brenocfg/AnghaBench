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
struct sata_start_req {int fis_type; int flags; int lbal; int sector_count; int ncqtag_atap_dir_m_dad; int /*<<< orphan*/  sata_fis; void* device_id; void* tag; int /*<<< orphan*/  command; } ;
struct sas_task {struct domain_device* dev; int /*<<< orphan*/  task_done; } ;
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {size_t device_id; int /*<<< orphan*/  id; } ;
struct pm8001_ccb_info {size_t ccb_tag; struct sas_task* task; struct pm8001_device* device; } ;
struct inbound_queue_table {int dummy; } ;
struct host_to_dev_fis {int fis_type; int flags; int lbal; int sector_count; int ncqtag_atap_dir_m_dad; int /*<<< orphan*/  sata_fis; void* device_id; void* tag; int /*<<< orphan*/  command; } ;
struct domain_device {struct pm8001_device* lldd_dev; } ;
typedef  int /*<<< orphan*/  sata_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_READ_LOG_EXT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NCQ_2ND_RLE_FLAG ; 
 int /*<<< orphan*/  NCQ_READ_LOG_FLAG ; 
 size_t OPC_INB_SATA_HOST_OPSTART ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (size_t) ; 
 struct domain_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sata_start_req*,int) ; 
 int /*<<< orphan*/  memset (struct sata_start_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,size_t,struct sata_start_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,size_t*) ; 
 int /*<<< orphan*/  pm8001_task_done ; 
 struct sas_task* sas_alloc_slow_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_free_task (struct sas_task*) ; 

__attribute__((used)) static void pm80xx_send_read_log(struct pm8001_hba_info *pm8001_ha,
		struct pm8001_device *pm8001_ha_dev)
{
	struct sata_start_req sata_cmd;
	int res;
	u32 ccb_tag;
	struct pm8001_ccb_info *ccb;
	struct sas_task *task = NULL;
	struct host_to_dev_fis fis;
	struct domain_device *dev;
	struct inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SATA_HOST_OPSTART;

	task = sas_alloc_slow_task(GFP_ATOMIC);

	if (!task) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("cannot allocate task !!!\n"));
		return;
	}
	task->task_done = pm8001_task_done;

	res = pm8001_tag_alloc(pm8001_ha, &ccb_tag);
	if (res) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("cannot allocate tag !!!\n"));
		return;
	}

	/* allocate domain device by ourselves as libsas
	 * is not going to provide any
	*/
	dev = kzalloc(sizeof(struct domain_device), GFP_ATOMIC);
	if (!dev) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Domain device cannot be allocated\n"));
		sas_free_task(task);
		return;
	} else {
		task->dev = dev;
		task->dev->lldd_dev = pm8001_ha_dev;
	}

	ccb = &pm8001_ha->ccb_info[ccb_tag];
	ccb->device = pm8001_ha_dev;
	ccb->ccb_tag = ccb_tag;
	ccb->task = task;
	pm8001_ha_dev->id |= NCQ_READ_LOG_FLAG;
	pm8001_ha_dev->id |= NCQ_2ND_RLE_FLAG;

	memset(&sata_cmd, 0, sizeof(sata_cmd));
	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	/* construct read log FIS */
	memset(&fis, 0, sizeof(struct host_to_dev_fis));
	fis.fis_type = 0x27;
	fis.flags = 0x80;
	fis.command = ATA_CMD_READ_LOG_EXT;
	fis.lbal = 0x10;
	fis.sector_count = 0x1;

	sata_cmd.tag = cpu_to_le32(ccb_tag);
	sata_cmd.device_id = cpu_to_le32(pm8001_ha_dev->device_id);
	sata_cmd.ncqtag_atap_dir_m_dad |= ((0x1 << 7) | (0x5 << 9));
	memcpy(&sata_cmd.sata_fis, &fis, sizeof(struct host_to_dev_fis));

	res = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &sata_cmd, 0);

}