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
struct scsi_device {int dummy; } ;
struct request {int cmd_len; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  retries; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_FLUSH_TIMEOUT ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SYNCHRONIZE_CACHE ; 
 int scsi_setup_blk_pc_cmnd (struct scsi_device*,struct request*) ; 

__attribute__((used)) static int scsi_setup_flush_cmnd(struct scsi_device *sdp, struct request *rq)
{
	rq->timeout = SD_FLUSH_TIMEOUT;
	rq->retries = SD_MAX_RETRIES;
	rq->cmd[0] = SYNCHRONIZE_CACHE;
	rq->cmd_len = 10;

	return scsi_setup_blk_pc_cmnd(sdp, rq);
}