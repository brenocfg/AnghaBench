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
struct request {int cmd_type; } ;

/* Variables and functions */
#define  REQ_TYPE_ATA_PC 131 
#define  REQ_TYPE_BLOCK_PC 130 
#define  REQ_TYPE_FS 129 
#define  REQ_TYPE_SENSE 128 
 int blk_rq_bytes (struct request*) ; 

int ide_cd_get_xferlen(struct request *rq)
{
	switch (rq->cmd_type) {
	case REQ_TYPE_FS:
		return 32768;
	case REQ_TYPE_SENSE:
	case REQ_TYPE_BLOCK_PC:
	case REQ_TYPE_ATA_PC:
		return blk_rq_bytes(rq);
	default:
		return 0;
	}
}