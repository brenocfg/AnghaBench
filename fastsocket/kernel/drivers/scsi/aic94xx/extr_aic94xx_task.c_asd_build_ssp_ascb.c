#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_12__ {int efb_prio_attr; int /*<<< orphan*/  cdb; int /*<<< orphan*/  lun; } ;
struct TYPE_11__ {int /*<<< orphan*/  tptt; int /*<<< orphan*/  hashed_src_addr; int /*<<< orphan*/  hashed_dest_addr; int /*<<< orphan*/  frame_type; } ;
struct TYPE_14__ {int proto_conn_rate; int /*<<< orphan*/  sg_element; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  data_dir; void* conn_handle; void* sister_scb; TYPE_5__ ssp_cmd; TYPE_4__ ssp_frame; int /*<<< orphan*/  total_xfer_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  opcode; } ;
struct scb {TYPE_7__ ssp_task; TYPE_1__ header; } ;
struct TYPE_13__ {int task_prio; int task_attr; int /*<<< orphan*/  cdb; scalar_t__ enable_first_burst; int /*<<< orphan*/  LUN; } ;
struct sas_task {size_t data_dir; TYPE_6__ ssp_task; int /*<<< orphan*/  total_xfer_len; struct domain_device* dev; } ;
struct domain_device {int linkrate; scalar_t__ lldd_dev; TYPE_3__* port; int /*<<< orphan*/  hashed_sas_addr; } ;
struct asd_ascb {int /*<<< orphan*/  tasklet_complete; struct scb* scb; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_10__ {TYPE_2__* ha; } ;
struct TYPE_9__ {int /*<<< orphan*/  hashed_sas_addr; } ;

/* Variables and functions */
 int EFB_MASK ; 
 int HASHED_SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  INITIATE_SSP_TASK ; 
 int /*<<< orphan*/  SSP_DATA ; 
 int asd_map_scatterlist (struct sas_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_task_tasklet_complete ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * data_dir_flags ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int asd_build_ssp_ascb(struct asd_ascb *ascb, struct sas_task *task,
			      gfp_t gfp_flags)
{
	struct domain_device *dev = task->dev;
	struct scb *scb;
	int    res = 0;

	scb = ascb->scb;

	scb->header.opcode = INITIATE_SSP_TASK;

	scb->ssp_task.proto_conn_rate  = (1 << 4); /* SSP */
	scb->ssp_task.proto_conn_rate |= dev->linkrate;
	scb->ssp_task.total_xfer_len = cpu_to_le32(task->total_xfer_len);
	scb->ssp_task.ssp_frame.frame_type = SSP_DATA;
	memcpy(scb->ssp_task.ssp_frame.hashed_dest_addr, dev->hashed_sas_addr,
	       HASHED_SAS_ADDR_SIZE);
	memcpy(scb->ssp_task.ssp_frame.hashed_src_addr,
	       dev->port->ha->hashed_sas_addr, HASHED_SAS_ADDR_SIZE);
	scb->ssp_task.ssp_frame.tptt = cpu_to_be16(0xFFFF);

	memcpy(scb->ssp_task.ssp_cmd.lun, task->ssp_task.LUN, 8);
	if (task->ssp_task.enable_first_burst)
		scb->ssp_task.ssp_cmd.efb_prio_attr |= EFB_MASK;
	scb->ssp_task.ssp_cmd.efb_prio_attr |= (task->ssp_task.task_prio << 3);
	scb->ssp_task.ssp_cmd.efb_prio_attr |= (task->ssp_task.task_attr & 7);
	memcpy(scb->ssp_task.ssp_cmd.cdb, task->ssp_task.cdb, 16);

	scb->ssp_task.sister_scb = cpu_to_le16(0xFFFF);
	scb->ssp_task.conn_handle = cpu_to_le16(
		(u16)(unsigned long)dev->lldd_dev);
	scb->ssp_task.data_dir = data_dir_flags[task->data_dir];
	scb->ssp_task.retry_count = scb->ssp_task.retry_count;

	ascb->tasklet_complete = asd_task_tasklet_complete;

	res = asd_map_scatterlist(task, scb->ssp_task.sg_element, gfp_flags);

	return res;
}