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
struct srp_target_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_reqs; int /*<<< orphan*/  req_lim; } ;
struct srp_request {int /*<<< orphan*/  list; } ;
struct scsi_cmnd {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  srp_unmap_data (struct scsi_cmnd*,struct srp_target_port*,struct srp_request*) ; 

__attribute__((used)) static void srp_free_req(struct srp_target_port *target,
			 struct srp_request *req, struct scsi_cmnd *scmnd,
			 s32 req_lim_delta)
{
	unsigned long flags;

	srp_unmap_data(scmnd, target, req);

	spin_lock_irqsave(&target->lock, flags);
	target->req_lim += req_lim_delta;
	list_add_tail(&req->list, &target->free_reqs);
	spin_unlock_irqrestore(&target->lock, flags);
}