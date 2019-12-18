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
struct TYPE_3__ {int max_cmds; int token_mask; int /*<<< orphan*/  poll_sem; int /*<<< orphan*/  flags; int /*<<< orphan*/  context_lock; int /*<<< orphan*/  event_sem; scalar_t__ free_head; TYPE_2__* context; } ;
struct mthca_dev {TYPE_1__ cmd; } ;
struct mthca_cmd_context {int dummy; } ;
struct TYPE_4__ {int token; int next; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTHCA_CMD_USE_EVENTS ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mthca_cmd_use_events(struct mthca_dev *dev)
{
	int i;

	dev->cmd.context = kmalloc(dev->cmd.max_cmds *
				   sizeof (struct mthca_cmd_context),
				   GFP_KERNEL);
	if (!dev->cmd.context)
		return -ENOMEM;

	for (i = 0; i < dev->cmd.max_cmds; ++i) {
		dev->cmd.context[i].token = i;
		dev->cmd.context[i].next = i + 1;
	}

	dev->cmd.context[dev->cmd.max_cmds - 1].next = -1;
	dev->cmd.free_head = 0;

	sema_init(&dev->cmd.event_sem, dev->cmd.max_cmds);
	spin_lock_init(&dev->cmd.context_lock);

	for (dev->cmd.token_mask = 1;
	     dev->cmd.token_mask < dev->cmd.max_cmds;
	     dev->cmd.token_mask <<= 1)
		; /* nothing */
	--dev->cmd.token_mask;

	dev->cmd.flags |= MTHCA_CMD_USE_EVENTS;

	down(&dev->cmd.poll_sem);

	return 0;
}