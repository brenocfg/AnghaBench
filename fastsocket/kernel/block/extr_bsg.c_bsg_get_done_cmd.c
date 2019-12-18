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
struct bsg_device {int /*<<< orphan*/  name; int /*<<< orphan*/  done_cmds; int /*<<< orphan*/  wq_done; int /*<<< orphan*/  flags; } ;
struct bsg_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSG_F_BLOCK ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 struct bsg_command* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct bsg_command* bsg_next_done_cmd (struct bsg_device*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct bsg_command*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bsg_command *bsg_get_done_cmd(struct bsg_device *bd)
{
	struct bsg_command *bc;
	int ret;

	do {
		bc = bsg_next_done_cmd(bd);
		if (bc)
			break;

		if (!test_bit(BSG_F_BLOCK, &bd->flags)) {
			bc = ERR_PTR(-EAGAIN);
			break;
		}

		ret = wait_event_interruptible(bd->wq_done, bd->done_cmds);
		if (ret) {
			bc = ERR_PTR(-ERESTARTSYS);
			break;
		}
	} while (1);

	dprintk("%s: returning done %p\n", bd->name, bc);

	return bc;
}