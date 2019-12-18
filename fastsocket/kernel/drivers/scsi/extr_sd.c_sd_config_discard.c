#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct scsi_disk {int lbprz; unsigned int unmap_alignment; unsigned int unmap_granularity; unsigned int provisioning_mode; int /*<<< orphan*/  max_ws_blocks; int /*<<< orphan*/  max_unmap_blocks; int /*<<< orphan*/  physical_block_size; TYPE_2__* device; TYPE_1__* disk; } ;
struct TYPE_6__ {int discard_zeroes_data; unsigned int discard_alignment; unsigned int max_discard_sectors; int /*<<< orphan*/  discard_granularity; } ;
struct request_queue {TYPE_3__ limits; } ;
struct TYPE_5__ {unsigned int sector_size; } ;
struct TYPE_4__ {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
#define  SD_LBP_DISABLE 132 
#define  SD_LBP_UNMAP 131 
#define  SD_LBP_WS10 130 
#define  SD_LBP_WS16 129 
#define  SD_LBP_ZERO 128 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int min_not_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_flag_clear_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 

__attribute__((used)) static void sd_config_discard(struct scsi_disk *sdkp, unsigned int mode)
{
	struct request_queue *q = sdkp->disk->queue;
	unsigned int logical_block_size = sdkp->device->sector_size;
	unsigned int max_blocks = 0;

	q->limits.discard_zeroes_data = sdkp->lbprz;
	q->limits.discard_alignment = sdkp->unmap_alignment *
		logical_block_size;
	q->limits.discard_granularity =
		max(sdkp->physical_block_size,
		    sdkp->unmap_granularity * logical_block_size);

	sdkp->provisioning_mode = mode;

	switch (mode) {

	case SD_LBP_DISABLE:
		q->limits.max_discard_sectors = 0;
		queue_flag_clear_unlocked(QUEUE_FLAG_DISCARD, q);
		return;

	case SD_LBP_UNMAP:
		max_blocks = min_not_zero(sdkp->max_unmap_blocks, 0xffffffff);
		break;

	case SD_LBP_WS16:
		max_blocks = min_not_zero(sdkp->max_ws_blocks, 0xffffffff);
		break;

	case SD_LBP_WS10:
		max_blocks = min_not_zero(sdkp->max_ws_blocks, (u32)0xffff);
		break;

	case SD_LBP_ZERO:
		max_blocks = min_not_zero(sdkp->max_ws_blocks, (u32)0xffff);
		q->limits.discard_zeroes_data = 1;
		break;
	}

	q->limits.max_discard_sectors = max_blocks * (logical_block_size >> 9);
	queue_flag_set_unlocked(QUEUE_FLAG_DISCARD, q);
}