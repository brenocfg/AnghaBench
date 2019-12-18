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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 struct request_queue* __scsi_alloc_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_lld_busy (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_prep_rq (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_rq_timed_out (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_softirq_done (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_lld_busy ; 
 int /*<<< orphan*/  scsi_prep_fn ; 
 int /*<<< orphan*/  scsi_request_fn ; 
 int /*<<< orphan*/  scsi_softirq_done ; 
 int /*<<< orphan*/  scsi_times_out ; 

struct request_queue *scsi_alloc_queue(struct scsi_device *sdev)
{
	struct request_queue *q;

	q = __scsi_alloc_queue(sdev->host, scsi_request_fn);
	if (!q)
		return NULL;

	blk_queue_prep_rq(q, scsi_prep_fn);
	blk_queue_softirq_done(q, scsi_softirq_done);
	blk_queue_rq_timed_out(q, scsi_times_out);
	blk_queue_lld_busy(q, scsi_lld_busy);
	return q;
}