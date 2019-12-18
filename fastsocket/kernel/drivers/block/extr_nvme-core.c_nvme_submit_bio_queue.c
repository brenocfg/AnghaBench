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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct nvme_queue {size_t sq_tail; size_t q_depth; int /*<<< orphan*/  dev; int /*<<< orphan*/  q_db; struct nvme_command* sq_cmds; } ;
struct nvme_ns {int lba_shift; int /*<<< orphan*/  ns_id; int /*<<< orphan*/  queue; } ;
struct nvme_iod {struct bio* private; } ;
struct TYPE_2__ {int command_id; void* dsmgmt; void* control; void* length; int /*<<< orphan*/  slba; void* nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ rw; int /*<<< orphan*/  common; } ;
struct bio {int bi_rw; int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_size; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int BIO_RW_AHEAD ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NVME_IO_TIMEOUT ; 
 int /*<<< orphan*/  NVME_RW_DSM_FREQ_PREFETCH ; 
 int NVME_RW_FUA ; 
 int NVME_RW_LR ; 
 int REQ_FAILFAST_DEV ; 
 int REQ_FLUSH ; 
 int REQ_FUA ; 
 int alloc_cmdid (struct nvme_queue*,struct nvme_iod*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_completion ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int bio_phys_segments (int /*<<< orphan*/ ,struct bio*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cmdid (struct nvme_queue*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 struct nvme_iod* nvme_alloc_iod (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_block_nr (struct nvme_ns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cmd_read ; 
 int /*<<< orphan*/  nvme_cmd_write ; 
 int /*<<< orphan*/  nvme_free_iod (int /*<<< orphan*/ ,struct nvme_iod*) ; 
 int nvme_map_bio (struct nvme_queue*,struct nvme_iod*,struct bio*,int,int) ; 
 int nvme_setup_prps (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nvme_iod*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_start_io_acct (struct bio*) ; 
 int nvme_submit_discard (struct nvme_queue*,struct nvme_ns*,struct bio*,struct nvme_iod*,int) ; 
 int nvme_submit_flush (struct nvme_queue*,struct nvme_ns*,int) ; 
 int nvme_submit_flush_data (struct nvme_queue*,struct nvme_ns*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_submit_bio_queue(struct nvme_queue *nvmeq, struct nvme_ns *ns,
								struct bio *bio)
{
	struct nvme_command *cmnd;
	struct nvme_iod *iod;
	enum dma_data_direction dma_dir;
	int cmdid, length, result;
	u16 control;
	u32 dsmgmt;
	int psegs = bio_phys_segments(ns->queue, bio);

	if ((bio->bi_rw & REQ_FLUSH) && psegs) {
		result = nvme_submit_flush_data(nvmeq, ns);
		if (result)
			return result;
	}

	result = -ENOMEM;
	iod = nvme_alloc_iod(psegs, bio->bi_size, GFP_ATOMIC);
	if (!iod)
		goto nomem;
	iod->private = bio;

	result = -EBUSY;
	cmdid = alloc_cmdid(nvmeq, iod, bio_completion, NVME_IO_TIMEOUT);
	if (unlikely(cmdid < 0))
		goto free_iod;

	if (bio->bi_rw & BIO_DISCARD) {
		result = nvme_submit_discard(nvmeq, ns, bio, iod, cmdid);
		if (result)
			goto free_cmdid;
		return result;
	}
	if ((bio->bi_rw & REQ_FLUSH) && !psegs)
		return nvme_submit_flush(nvmeq, ns, cmdid);

	control = 0;
	if (bio->bi_rw & REQ_FUA)
		control |= NVME_RW_FUA;
	if (bio->bi_rw & (REQ_FAILFAST_DEV | BIO_RW_AHEAD))
		control |= NVME_RW_LR;

	dsmgmt = 0;
	if (bio->bi_rw & BIO_RW_AHEAD)
		dsmgmt |= NVME_RW_DSM_FREQ_PREFETCH;

	cmnd = &nvmeq->sq_cmds[nvmeq->sq_tail];

	memset(cmnd, 0, sizeof(*cmnd));
	if (bio_data_dir(bio)) {
		cmnd->rw.opcode = nvme_cmd_write;
		dma_dir = DMA_TO_DEVICE;
	} else {
		cmnd->rw.opcode = nvme_cmd_read;
		dma_dir = DMA_FROM_DEVICE;
	}

	result = nvme_map_bio(nvmeq, iod, bio, dma_dir, psegs);
	if (result <= 0)
		goto free_cmdid;
	length = result;

	cmnd->rw.command_id = cmdid;
	cmnd->rw.nsid = cpu_to_le32(ns->ns_id);
	length = nvme_setup_prps(nvmeq->dev, &cmnd->common, iod, length,
								GFP_ATOMIC);
	cmnd->rw.slba = cpu_to_le64(nvme_block_nr(ns, bio->bi_sector));
	cmnd->rw.length = cpu_to_le16((length >> ns->lba_shift) - 1);
	cmnd->rw.control = cpu_to_le16(control);
	cmnd->rw.dsmgmt = cpu_to_le32(dsmgmt);

	nvme_start_io_acct(bio);
	if (++nvmeq->sq_tail == nvmeq->q_depth)
		nvmeq->sq_tail = 0;
	writel(nvmeq->sq_tail, nvmeq->q_db);

	return 0;

 free_cmdid:
	free_cmdid(nvmeq, cmdid, NULL);
 free_iod:
	nvme_free_iod(nvmeq->dev, iod);
 nomem:
	return result;
}