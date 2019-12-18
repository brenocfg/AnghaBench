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
struct bsg_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  queued_cmds; int /*<<< orphan*/  name; } ;
struct bsg_command {int /*<<< orphan*/  bidi_bio; int /*<<< orphan*/  bio; int /*<<< orphan*/  hdr; int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ IS_ERR (struct bsg_command*) ; 
 int blk_complete_sgv4_hdr_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsg_free_command (struct bsg_command*) ; 
 struct bsg_command* bsg_get_done_cmd (struct bsg_device*) ; 
 int bsg_io_schedule (struct bsg_device*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bsg_complete_all_commands(struct bsg_device *bd)
{
	struct bsg_command *bc;
	int ret, tret;

	dprintk("%s: entered\n", bd->name);

	/*
	 * wait for all commands to complete
	 */
	ret = 0;
	do {
		ret = bsg_io_schedule(bd);
		/*
		 * look for -ENODATA specifically -- we'll sometimes get
		 * -ERESTARTSYS when we've taken a signal, but we can't
		 * return until we're done freeing the queue, so ignore
		 * it.  The signal will get handled when we're done freeing
		 * the bsg_device.
		 */
	} while (ret != -ENODATA);

	/*
	 * discard done commands
	 */
	ret = 0;
	do {
		spin_lock_irq(&bd->lock);
		if (!bd->queued_cmds) {
			spin_unlock_irq(&bd->lock);
			break;
		}
		spin_unlock_irq(&bd->lock);

		bc = bsg_get_done_cmd(bd);
		if (IS_ERR(bc))
			break;

		tret = blk_complete_sgv4_hdr_rq(bc->rq, &bc->hdr, bc->bio,
						bc->bidi_bio);
		if (!ret)
			ret = tret;

		bsg_free_command(bc);
	} while (1);

	return ret;
}