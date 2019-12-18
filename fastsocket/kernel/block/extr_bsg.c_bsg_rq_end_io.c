#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {struct bsg_command* end_io_data; } ;
struct bsg_device {int /*<<< orphan*/  wq_done; int /*<<< orphan*/  lock; int /*<<< orphan*/  done_cmds; int /*<<< orphan*/  done_list; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ duration; } ;
struct bsg_command {int /*<<< orphan*/  list; TYPE_1__ hdr; int /*<<< orphan*/  bio; struct bsg_device* bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct request*,struct bsg_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bsg_rq_end_io(struct request *rq, int uptodate)
{
	struct bsg_command *bc = rq->end_io_data;
	struct bsg_device *bd = bc->bd;
	unsigned long flags;

	dprintk("%s: finished rq %p bc %p, bio %p stat %d\n",
		bd->name, rq, bc, bc->bio, uptodate);

	bc->hdr.duration = jiffies_to_msecs(jiffies - bc->hdr.duration);

	spin_lock_irqsave(&bd->lock, flags);
	list_move_tail(&bc->list, &bd->done_list);
	bd->done_cmds++;
	spin_unlock_irqrestore(&bd->lock, flags);

	wake_up(&bd->wq_done);
}