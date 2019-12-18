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
typedef  int /*<<< orphan*/  u32 ;
struct slic_hostcmd {struct slic_hostcmd* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
struct slic_cmdqueue {TYPE_1__ lock; struct slic_hostcmd* head; int /*<<< orphan*/  count; } ;
struct adapter {struct slic_cmdqueue cmdq_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  slic_cmdq_addcmdpage (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slic_cmdq_getdone (struct adapter*) ; 
 int /*<<< orphan*/ * slic_cmdqmem_addpage (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct slic_hostcmd *slic_cmdq_getfree(struct adapter *adapter)
{
	struct slic_cmdqueue *cmdq = &adapter->cmdq_free;
	struct slic_hostcmd *cmd = NULL;

lock_and_retry:
	spin_lock_irqsave(&cmdq->lock.lock, cmdq->lock.flags);
retry:
	cmd = cmdq->head;
	if (cmd) {
		cmdq->head = cmd->next;
		cmdq->count--;
		spin_unlock_irqrestore(&cmdq->lock.lock, cmdq->lock.flags);
	} else {
		slic_cmdq_getdone(adapter);
		cmd = cmdq->head;
		if (cmd) {
			goto retry;
		} else {
			u32 *pageaddr;

			spin_unlock_irqrestore(&cmdq->lock.lock,
						cmdq->lock.flags);
			pageaddr = slic_cmdqmem_addpage(adapter);
			if (pageaddr) {
				slic_cmdq_addcmdpage(adapter, pageaddr);
				goto lock_and_retry;
			}
		}
	}
	return cmd;
}