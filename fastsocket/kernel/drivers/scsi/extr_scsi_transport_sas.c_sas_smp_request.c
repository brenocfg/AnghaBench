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
struct sas_rphy {int dummy; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int /*<<< orphan*/  errors; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_4__ {TYPE_1__* f; } ;
struct TYPE_3__ {int (* smp_handler ) (struct Scsi_Host*,struct sas_rphy*,struct request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blk_end_request_all (struct request*,int) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_plugged (struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sas_smp_request(struct request_queue *q, struct Scsi_Host *shost,
			    struct sas_rphy *rphy)
{
	struct request *req;
	int ret;
	int (*handler)(struct Scsi_Host *, struct sas_rphy *, struct request *);

	while (!blk_queue_plugged(q)) {
		req = blk_fetch_request(q);
		if (!req)
			break;

		spin_unlock_irq(q->queue_lock);

		handler = to_sas_internal(shost->transportt)->f->smp_handler;
		ret = handler(shost, rphy, req);
		req->errors = ret;

		blk_end_request_all(req, ret);

		spin_lock_irq(q->queue_lock);
	}
}