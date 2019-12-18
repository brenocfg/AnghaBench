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
struct srp_target_port {int /*<<< orphan*/  lock; } ;
struct srp_request {struct scsi_cmnd* scmnd; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct scsi_cmnd *srp_claim_req(struct srp_target_port *target,
				       struct srp_request *req,
				       struct scsi_cmnd *scmnd)
{
	unsigned long flags;

	spin_lock_irqsave(&target->lock, flags);
	if (!scmnd) {
		scmnd = req->scmnd;
		req->scmnd = NULL;
	} else if (req->scmnd == scmnd) {
		req->scmnd = NULL;
	} else {
		scmnd = NULL;
	}
	spin_unlock_irqrestore(&target->lock, flags);

	return scmnd;
}