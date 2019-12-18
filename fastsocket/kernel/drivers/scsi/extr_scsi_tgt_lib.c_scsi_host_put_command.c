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
struct scsi_tgt_cmd {int dummy; } ;
struct scsi_cmnd {struct request* request; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {struct scsi_tgt_cmd* end_io_data; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; struct request_queue* uspace_req_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_put_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  __scsi_put_command (struct Scsi_Host*,struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct scsi_tgt_cmd*) ; 
 int /*<<< orphan*/  scsi_tgt_cmd_cache ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void scsi_host_put_command(struct Scsi_Host *shost, struct scsi_cmnd *cmd)
{
	struct request_queue *q = shost->uspace_req_q;
	struct request *rq = cmd->request;
	struct scsi_tgt_cmd *tcmd = rq->end_io_data;
	unsigned long flags;

	kmem_cache_free(scsi_tgt_cmd_cache, tcmd);

	spin_lock_irqsave(q->queue_lock, flags);
	__blk_put_request(q, rq);
	spin_unlock_irqrestore(q->queue_lock, flags);

	__scsi_put_command(shost, cmd, &shost->shost_gendev);
}