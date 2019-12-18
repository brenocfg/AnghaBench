#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mspro_param_register {int /*<<< orphan*/  data_address; scalar_t__ tpc_param; int /*<<< orphan*/  data_count; int /*<<< orphan*/  system; } ;
struct mspro_block_data {unsigned int page_size; scalar_t__ data_dir; TYPE_1__* block_req; int /*<<< orphan*/  queue; int /*<<< orphan*/  mrq_handler; int /*<<< orphan*/  transfer_cmd; int /*<<< orphan*/  system; int /*<<< orphan*/  seg_count; int /*<<< orphan*/  req_sg; scalar_t__ current_seg; scalar_t__ current_page; } ;
struct memstick_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  host; int /*<<< orphan*/  current_mrq; int /*<<< orphan*/  next_request; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  param ;
struct TYPE_7__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MSPRO_CMD_READ_DATA ; 
 int /*<<< orphan*/  MSPRO_CMD_WRITE_DATA ; 
 int /*<<< orphan*/  MS_TPC_WRITE_REG ; 
 scalar_t__ READ ; 
 int __blk_end_request_cur (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* blk_fetch_request (int /*<<< orphan*/ ) ; 
 unsigned int blk_rq_bytes (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_rq_map_sg (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int blk_rq_pos (TYPE_1__*) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  h_mspro_block_req_init ; 
 int /*<<< orphan*/  h_mspro_block_transfer_data ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  memstick_init_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mspro_param_register*,int) ; 
 int /*<<< orphan*/  memstick_new_req (int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (TYPE_1__*) ; 
 int /*<<< orphan*/  sector_div (int,unsigned int) ; 

__attribute__((used)) static int mspro_block_issue_req(struct memstick_dev *card, int chunk)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	sector_t t_sec;
	unsigned int count;
	struct mspro_param_register param;

try_again:
	while (chunk) {
		msb->current_page = 0;
		msb->current_seg = 0;
		msb->seg_count = blk_rq_map_sg(msb->block_req->q,
					       msb->block_req,
					       msb->req_sg);

		if (!msb->seg_count) {
			chunk = __blk_end_request_cur(msb->block_req, -ENOMEM);
			continue;
		}

		t_sec = blk_rq_pos(msb->block_req) << 9;
		sector_div(t_sec, msb->page_size);

		count = blk_rq_bytes(msb->block_req);
		count /= msb->page_size;

		param.system = msb->system;
		param.data_count = cpu_to_be16(count);
		param.data_address = cpu_to_be32((uint32_t)t_sec);
		param.tpc_param = 0;

		msb->data_dir = rq_data_dir(msb->block_req);
		msb->transfer_cmd = msb->data_dir == READ
				    ? MSPRO_CMD_READ_DATA
				    : MSPRO_CMD_WRITE_DATA;

		dev_dbg(&card->dev, "data transfer: cmd %x, "
			"lba %x, count %x\n", msb->transfer_cmd,
			be32_to_cpu(param.data_address), count);

		card->next_request = h_mspro_block_req_init;
		msb->mrq_handler = h_mspro_block_transfer_data;
		memstick_init_req(&card->current_mrq, MS_TPC_WRITE_REG,
				  &param, sizeof(param));
		memstick_new_req(card->host);
		return 0;
	}

	dev_dbg(&card->dev, "blk_fetch\n");
	msb->block_req = blk_fetch_request(msb->queue);
	if (!msb->block_req) {
		dev_dbg(&card->dev, "issue end\n");
		return -EAGAIN;
	}

	dev_dbg(&card->dev, "trying again\n");
	chunk = 1;
	goto try_again;
}