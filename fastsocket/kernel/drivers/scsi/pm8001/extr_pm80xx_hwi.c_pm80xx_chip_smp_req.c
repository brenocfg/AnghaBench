#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_3__ {void* long_resp_size; void* long_resp_addr; void* long_req_size; void* long_req_addr; } ;
struct smp_req {char* smp_req16; char* smp_req; void* tag; TYPE_1__ long_smp_req; } ;
struct scatterlist {int length; } ;
struct TYPE_4__ {struct scatterlist smp_req; struct scatterlist smp_resp; } ;
struct sas_task {TYPE_2__ smp_task; struct domain_device* dev; } ;
struct pm8001_hba_info {void* smp_exp_mode; int /*<<< orphan*/  dev; struct inbound_queue_table* inbnd_q_tbl; } ;
struct pm8001_device {int /*<<< orphan*/  device_id; } ;
struct pm8001_ccb_info {int ccb_tag; struct sas_task* task; } ;
struct inbound_queue_table {int dummy; } ;
struct domain_device {struct pm8001_device* lldd_dev; } ;
typedef  int /*<<< orphan*/  smp_cmd ;
typedef  void* __le64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int OPC_INB_SMP_REQUEST ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  PM8001_IO_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 void* SMP_DIRECT ; 
 void* SMP_INDIRECT ; 
 int /*<<< orphan*/  build_smp_cmd (int /*<<< orphan*/ ,void*,struct smp_req*,void*,int) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smp_req*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ phys_to_virt (void*) ; 
 int /*<<< orphan*/  pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static int pm80xx_chip_smp_req(struct pm8001_hba_info *pm8001_ha,
	struct pm8001_ccb_info *ccb)
{
	int elem, rc;
	struct sas_task *task = ccb->task;
	struct domain_device *dev = task->dev;
	struct pm8001_device *pm8001_dev = dev->lldd_dev;
	struct scatterlist *sg_req, *sg_resp;
	u32 req_len, resp_len;
	struct smp_req smp_cmd;
	u32 opc;
	struct inbound_queue_table *circularQ;
	char *preq_dma_addr = NULL;
	__le64 tmp_addr;
	u32 i, length;

	memset(&smp_cmd, 0, sizeof(smp_cmd));
	/*
	 * DMA-map SMP request, response buffers
	 */
	sg_req = &task->smp_task.smp_req;
	elem = dma_map_sg(pm8001_ha->dev, sg_req, 1, PCI_DMA_TODEVICE);
	if (!elem)
		return -ENOMEM;
	req_len = sg_dma_len(sg_req);

	sg_resp = &task->smp_task.smp_resp;
	elem = dma_map_sg(pm8001_ha->dev, sg_resp, 1, PCI_DMA_FROMDEVICE);
	if (!elem) {
		rc = -ENOMEM;
		goto err_out;
	}
	resp_len = sg_dma_len(sg_resp);
	/* must be in dwords */
	if ((req_len & 0x3) || (resp_len & 0x3)) {
		rc = -EINVAL;
		goto err_out_2;
	}

	opc = OPC_INB_SMP_REQUEST;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	smp_cmd.tag = cpu_to_le32(ccb->ccb_tag);

	length = sg_req->length;
	PM8001_IO_DBG(pm8001_ha,
		pm8001_printk("SMP Frame Length %d\n", sg_req->length));
	if (!(length - 8))
		pm8001_ha->smp_exp_mode = SMP_DIRECT;
	else
		pm8001_ha->smp_exp_mode = SMP_INDIRECT;

	/* DIRECT MODE support only in spcv/ve */
	pm8001_ha->smp_exp_mode = SMP_DIRECT;

	tmp_addr = cpu_to_le64((u64)sg_dma_address(&task->smp_task.smp_req));
	preq_dma_addr = (char *)phys_to_virt(tmp_addr);

	/* INDIRECT MODE command settings. Use DMA */
	if (pm8001_ha->smp_exp_mode == SMP_INDIRECT) {
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("SMP REQUEST INDIRECT MODE\n"));
		/* for SPCv indirect mode. Place the top 4 bytes of
		 * SMP Request header here. */
		for (i = 0; i < 4; i++)
			smp_cmd.smp_req16[i] = *(preq_dma_addr + i);
		/* exclude top 4 bytes for SMP req header */
		smp_cmd.long_smp_req.long_req_addr =
			cpu_to_le64((u64)sg_dma_address
				(&task->smp_task.smp_req) - 4);
		/* exclude 4 bytes for SMP req header and CRC */
		smp_cmd.long_smp_req.long_req_size =
			cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_req)-8);
		smp_cmd.long_smp_req.long_resp_addr =
				cpu_to_le64((u64)sg_dma_address
					(&task->smp_task.smp_resp));
		smp_cmd.long_smp_req.long_resp_size =
				cpu_to_le32((u32)sg_dma_len
					(&task->smp_task.smp_resp)-4);
	} else { /* DIRECT MODE */
		smp_cmd.long_smp_req.long_req_addr =
			cpu_to_le64((u64)sg_dma_address
					(&task->smp_task.smp_req));
		smp_cmd.long_smp_req.long_req_size =
			cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_req)-4);
		smp_cmd.long_smp_req.long_resp_addr =
			cpu_to_le64((u64)sg_dma_address
				(&task->smp_task.smp_resp));
		smp_cmd.long_smp_req.long_resp_size =
			cpu_to_le32
			((u32)sg_dma_len(&task->smp_task.smp_resp)-4);
	}
	if (pm8001_ha->smp_exp_mode == SMP_DIRECT) {
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("SMP REQUEST DIRECT MODE\n"));
		for (i = 0; i < length; i++)
			if (i < 16) {
				smp_cmd.smp_req16[i] = *(preq_dma_addr+i);
				PM8001_IO_DBG(pm8001_ha, pm8001_printk(
					"Byte[%d]:%x (DMA data:%x)\n",
					i, smp_cmd.smp_req16[i],
					*(preq_dma_addr)));
			} else {
				smp_cmd.smp_req[i] = *(preq_dma_addr+i);
				PM8001_IO_DBG(pm8001_ha, pm8001_printk(
					"Byte[%d]:%x (DMA data:%x)\n",
					i, smp_cmd.smp_req[i],
					*(preq_dma_addr)));
			}
	}

	build_smp_cmd(pm8001_dev->device_id, smp_cmd.tag,
				&smp_cmd, pm8001_ha->smp_exp_mode, length);
	pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, (u32 *)&smp_cmd, 0);
	return 0;

err_out_2:
	dma_unmap_sg(pm8001_ha->dev, &ccb->task->smp_task.smp_resp, 1,
			PCI_DMA_FROMDEVICE);
err_out:
	dma_unmap_sg(pm8001_ha->dev, &ccb->task->smp_task.smp_req, 1,
			PCI_DMA_TODEVICE);
	return rc;
}