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
struct scsi_tgt_queuedata {int /*<<< orphan*/  cmd_hash_lock; int /*<<< orphan*/ * cmd_hash; struct Scsi_Host* shost; } ;
struct request_queue {int /*<<< orphan*/  nr_requests; struct scsi_tgt_queuedata* queuedata; } ;
struct Scsi_Host {struct request_queue* uspace_req_q; int /*<<< orphan*/  can_queue; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct request_queue* __scsi_alloc_queue (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_dma_alignment (struct request_queue*,int /*<<< orphan*/ ) ; 
 struct scsi_tgt_queuedata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int scsi_tgt_alloc_queue(struct Scsi_Host *shost)
{
	struct scsi_tgt_queuedata *queuedata;
	struct request_queue *q;
	int err, i;

	/*
	 * Do we need to send a netlink event or should uspace
	 * just respond to the hotplug event?
	 */
	q = __scsi_alloc_queue(shost, NULL);
	if (!q)
		return -ENOMEM;

	queuedata = kzalloc(sizeof(*queuedata), GFP_KERNEL);
	if (!queuedata) {
		err = -ENOMEM;
		goto cleanup_queue;
	}
	queuedata->shost = shost;
	q->queuedata = queuedata;

	/*
	 * this is a silly hack. We should probably just queue as many
	 * command as is recvd to userspace. uspace can then make
	 * sure we do not overload the HBA
	 */
	q->nr_requests = shost->can_queue;
	/*
	 * We currently only support software LLDs so this does
	 * not matter for now. Do we need this for the cards we support?
	 * If so we should make it a host template value.
	 */
	blk_queue_dma_alignment(q, 0);
	shost->uspace_req_q = q;

	for (i = 0; i < ARRAY_SIZE(queuedata->cmd_hash); i++)
		INIT_LIST_HEAD(&queuedata->cmd_hash[i]);
	spin_lock_init(&queuedata->cmd_hash_lock);

	return 0;

cleanup_queue:
	blk_cleanup_queue(q);
	return err;
}