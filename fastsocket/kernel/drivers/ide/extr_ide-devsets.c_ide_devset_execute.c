#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int cmd_len; int (* special ) (TYPE_1__*,int) ;int errors; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  cmd_type; } ;
struct ide_devset {int flags; int (* set ) (TYPE_1__*,int) ;} ;
struct TYPE_4__ {struct request_queue* queue; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int DS_SYNC ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_DEVSET_EXEC ; 
 int /*<<< orphan*/  REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 scalar_t__ blk_execute_rq (struct request_queue*,int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int stub1 (TYPE_1__*,int) ; 

int ide_devset_execute(ide_drive_t *drive, const struct ide_devset *setting,
		       int arg)
{
	struct request_queue *q = drive->queue;
	struct request *rq;
	int ret = 0;

	if (!(setting->flags & DS_SYNC))
		return setting->set(drive, arg);

	rq = blk_get_request(q, READ, __GFP_WAIT);
	rq->cmd_type = REQ_TYPE_SPECIAL;
	rq->cmd_len = 5;
	rq->cmd[0] = REQ_DEVSET_EXEC;
	*(int *)&rq->cmd[1] = arg;
	rq->special = setting->set;

	if (blk_execute_rq(q, NULL, rq, 0))
		ret = rq->errors;
	blk_put_request(rq);

	return ret;
}