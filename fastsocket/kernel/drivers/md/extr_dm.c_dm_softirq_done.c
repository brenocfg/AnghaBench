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
struct request {int cmd_flags; struct dm_rq_target_io* end_io_data; struct request* completion_data; } ;
struct dm_rq_target_io {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int REQ_FAILED ; 
 int /*<<< orphan*/  dm_done (struct request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm_softirq_done(struct request *rq)
{
	bool mapped = true;
	struct request *clone = rq->completion_data;
	struct dm_rq_target_io *tio = clone->end_io_data;

	if (rq->cmd_flags & REQ_FAILED)
		mapped = false;

	dm_done(clone, tio->error, mapped);
}