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
struct request_queue {int dummy; } ;
struct request {long* cmd; int cmd_len; } ;

/* Variables and functions */
 int BLKPREP_OK ; 
 int /*<<< orphan*/  BLK_MAX_CDB ; 
 long GPCMD_READ_10 ; 
 long GPCMD_WRITE_10 ; 
 scalar_t__ READ ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  memset (long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int queue_logical_block_size (struct request_queue*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static int ide_cdrom_prep_fs(struct request_queue *q, struct request *rq)
{
	int hard_sect = queue_logical_block_size(q);
	long block = (long)blk_rq_pos(rq) / (hard_sect >> 9);
	unsigned long blocks = blk_rq_sectors(rq) / (hard_sect >> 9);

	memset(rq->cmd, 0, BLK_MAX_CDB);

	if (rq_data_dir(rq) == READ)
		rq->cmd[0] = GPCMD_READ_10;
	else
		rq->cmd[0] = GPCMD_WRITE_10;

	/*
	 * fill in lba
	 */
	rq->cmd[2] = (block >> 24) & 0xff;
	rq->cmd[3] = (block >> 16) & 0xff;
	rq->cmd[4] = (block >>  8) & 0xff;
	rq->cmd[5] = block & 0xff;

	/*
	 * and transfer length
	 */
	rq->cmd[7] = (blocks >> 8) & 0xff;
	rq->cmd[8] = blocks & 0xff;
	rq->cmd_len = 10;
	return BLKPREP_OK;
}