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
struct request {unsigned int errors; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int) ; 

__attribute__((used)) static void ub_end_rq(struct request *rq, unsigned int scsi_status)
{
	int error;

	if (scsi_status == 0) {
		error = 0;
	} else {
		error = -EIO;
		rq->errors = scsi_status;
	}
	__blk_end_request_all(rq, error);
}