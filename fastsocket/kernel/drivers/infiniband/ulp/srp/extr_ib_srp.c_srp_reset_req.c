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
struct srp_target_port {int dummy; } ;
struct srp_request {int dummy; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;

/* Variables and functions */
 int DID_RESET ; 
 struct scsi_cmnd* srp_claim_req (struct srp_target_port*,struct srp_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_free_req (struct srp_target_port*,struct srp_request*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void srp_reset_req(struct srp_target_port *target, struct srp_request *req)
{
	struct scsi_cmnd *scmnd = srp_claim_req(target, req, NULL);

	if (scmnd) {
		srp_free_req(target, req, scmnd, 0);
		scmnd->result = DID_RESET << 16;
		scmnd->scsi_done(scmnd);
	}
}