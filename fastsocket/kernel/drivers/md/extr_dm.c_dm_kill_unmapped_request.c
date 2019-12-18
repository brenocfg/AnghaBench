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
struct request {int /*<<< orphan*/  cmd_flags; struct dm_rq_target_io* end_io_data; } ;
struct dm_rq_target_io {struct request* orig; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_FAILED ; 
 int /*<<< orphan*/  dm_complete_request (struct request*,int) ; 

void dm_kill_unmapped_request(struct request *clone, int error)
{
	struct dm_rq_target_io *tio = clone->end_io_data;
	struct request *rq = tio->orig;

	rq->cmd_flags |= REQ_FAILED;
	dm_complete_request(clone, error);
}