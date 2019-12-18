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
struct nvme_queue {size_t sq_tail; size_t q_depth; int /*<<< orphan*/  q_db; TYPE_1__* dev; struct nvme_command* sq_cmds; } ;
struct nvme_ns {int lba_shift; int ns_id; } ;
struct nvme_iod {int /*<<< orphan*/  first_dma; scalar_t__ npages; } ;
struct nvme_dsm_range {void* slba; void* nlb; void* cattr; } ;
struct TYPE_4__ {int command_id; void* attributes; scalar_t__ nr; void* prp1; void* nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_2__ dsm; } ;
struct bio {int bi_size; int /*<<< orphan*/  bi_sector; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_3__ {int /*<<< orphan*/  prp_small_pool; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NVME_DSMGMT_AD ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct nvme_dsm_range* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** iod_list (struct nvme_iod*) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_block_nr (struct nvme_ns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cmd_dsm ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_submit_discard(struct nvme_queue *nvmeq, struct nvme_ns *ns,
		struct bio *bio, struct nvme_iod *iod, int cmdid)
{
	struct nvme_dsm_range *range;
	struct nvme_command *cmnd = &nvmeq->sq_cmds[nvmeq->sq_tail];

	range = dma_pool_alloc(nvmeq->dev->prp_small_pool, GFP_ATOMIC,
							&iod->first_dma);
	if (!range)
		return -ENOMEM;

	iod_list(iod)[0] = (__le64 *)range;
	iod->npages = 0;

	range->cattr = cpu_to_le32(0);
	range->nlb = cpu_to_le32(bio->bi_size >> ns->lba_shift);
	range->slba = cpu_to_le64(nvme_block_nr(ns, bio->bi_sector));

	memset(cmnd, 0, sizeof(*cmnd));
	cmnd->dsm.opcode = nvme_cmd_dsm;
	cmnd->dsm.command_id = cmdid;
	cmnd->dsm.nsid = cpu_to_le32(ns->ns_id);
	cmnd->dsm.prp1 = cpu_to_le64(iod->first_dma);
	cmnd->dsm.nr = 0;
	cmnd->dsm.attributes = cpu_to_le32(NVME_DSMGMT_AD);

	if (++nvmeq->sq_tail == nvmeq->q_depth)
		nvmeq->sq_tail = 0;
	writel(nvmeq->sq_tail, nvmeq->q_db);

	return 0;
}