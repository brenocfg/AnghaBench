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
struct request_queue {struct request* boundary_rq; int /*<<< orphan*/  end_sector; } ;
struct request {int cmd_flags; scalar_t__ cmd_type; } ;

/* Variables and functions */
 int ELEVATOR_INSERT_BACK ; 
 int ELEVATOR_INSERT_SORT ; 
 int REQ_ELVPRIV ; 
 int REQ_HARDBARRIER ; 
 int REQ_SOFTBARRIER ; 
 scalar_t__ REQ_TYPE_FS ; 
 int /*<<< orphan*/  blk_plug_device (struct request_queue*) ; 
 int /*<<< orphan*/  elv_insert (struct request_queue*,struct request*,int) ; 
 int /*<<< orphan*/  rq_end_sector (struct request*) ; 

void __elv_add_request(struct request_queue *q, struct request *rq, int where,
		       int plug)
{
	if (rq->cmd_flags & (REQ_SOFTBARRIER | REQ_HARDBARRIER)) {
		/* barriers are scheduling boundary, update end_sector */
		if (rq->cmd_type == REQ_TYPE_FS) {
			q->end_sector = rq_end_sector(rq);
			q->boundary_rq = rq;
		}
	} else if (!(rq->cmd_flags & REQ_ELVPRIV) &&
		    where == ELEVATOR_INSERT_SORT)
		where = ELEVATOR_INSERT_BACK;

	if (plug)
		blk_plug_device(q);

	elv_insert(q, rq, where);
}