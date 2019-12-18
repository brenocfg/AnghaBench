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
struct st_request {scalar_t__ waiting; struct bio* bio; int /*<<< orphan*/  result; struct scsi_tape* stp; } ;
struct scsi_tape {TYPE_2__* buffer; } ;
struct request {int /*<<< orphan*/  q; int /*<<< orphan*/  resid_len; int /*<<< orphan*/  errors; struct st_request* end_io_data; } ;
struct bio {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  residual; int /*<<< orphan*/  midlevel_result; } ;
struct TYPE_4__ {TYPE_1__ cmdstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_put_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  blk_rq_unmap_user (struct bio*) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 

__attribute__((used)) static void st_scsi_execute_end(struct request *req, int uptodate)
{
	struct st_request *SRpnt = req->end_io_data;
	struct scsi_tape *STp = SRpnt->stp;
	struct bio *tmp;

	STp->buffer->cmdstat.midlevel_result = SRpnt->result = req->errors;
	STp->buffer->cmdstat.residual = req->resid_len;

	tmp = SRpnt->bio;
	if (SRpnt->waiting)
		complete(SRpnt->waiting);

	blk_rq_unmap_user(tmp);
	__blk_put_request(req->q, req);
}