#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_8__ {void* size; void* bus_addr; } ;
struct TYPE_7__ {void* size; void* bus_addr; } ;
struct TYPE_10__ {void* conn_handle; void* sister_scb; TYPE_3__ smp_resp; TYPE_2__ smp_req; int /*<<< orphan*/  proto_conn_rate; } ;
struct TYPE_6__ {int /*<<< orphan*/  opcode; } ;
struct scb {TYPE_5__ smp_task; TYPE_1__ header; } ;
struct TYPE_9__ {int /*<<< orphan*/  smp_resp; int /*<<< orphan*/  smp_req; } ;
struct sas_task {TYPE_4__ smp_task; struct domain_device* dev; } ;
struct domain_device {scalar_t__ lldd_dev; int /*<<< orphan*/  linkrate; } ;
struct asd_ha_struct {int /*<<< orphan*/  pcidev; } ;
struct asd_ascb {int /*<<< orphan*/  tasklet_complete; struct scb* scb; struct asd_ha_struct* ha; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INITIATE_SMP_TASK ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  asd_task_tasklet_complete ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sg_dma_address (int /*<<< orphan*/ *) ; 
 scalar_t__ sg_dma_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asd_build_smp_ascb(struct asd_ascb *ascb, struct sas_task *task,
			      gfp_t gfp_flags)
{
	struct asd_ha_struct *asd_ha = ascb->ha;
	struct domain_device *dev = task->dev;
	struct scb *scb;

	pci_map_sg(asd_ha->pcidev, &task->smp_task.smp_req, 1,
		   PCI_DMA_TODEVICE);
	pci_map_sg(asd_ha->pcidev, &task->smp_task.smp_resp, 1,
		   PCI_DMA_FROMDEVICE);

	scb = ascb->scb;

	scb->header.opcode = INITIATE_SMP_TASK;

	scb->smp_task.proto_conn_rate = dev->linkrate;

	scb->smp_task.smp_req.bus_addr =
		cpu_to_le64((u64)sg_dma_address(&task->smp_task.smp_req));
	scb->smp_task.smp_req.size =
		cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_req)-4);

	scb->smp_task.smp_resp.bus_addr =
		cpu_to_le64((u64)sg_dma_address(&task->smp_task.smp_resp));
	scb->smp_task.smp_resp.size =
		cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_resp)-4);

	scb->smp_task.sister_scb = cpu_to_le16(0xFFFF);
	scb->smp_task.conn_handle = cpu_to_le16((u16)
						(unsigned long)dev->lldd_dev);

	ascb->tasklet_complete = asd_task_tasklet_complete;

	return 0;
}