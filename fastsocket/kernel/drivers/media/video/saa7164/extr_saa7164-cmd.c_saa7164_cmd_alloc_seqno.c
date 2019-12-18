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
struct saa7164_dev {int /*<<< orphan*/  lock; TYPE_1__* cmds; } ;
struct TYPE_2__ {int inuse; int seqno; scalar_t__ timeout; scalar_t__ signalled; } ;

/* Variables and functions */
 int SAA_CMD_MAX_MSG_UNITS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int saa7164_cmd_alloc_seqno(struct saa7164_dev *dev)
{
	int i, ret = -1;

	mutex_lock(&dev->lock);
	for (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) {
		if (dev->cmds[i].inuse == 0) {
			dev->cmds[i].inuse = 1;
			dev->cmds[i].signalled = 0;
			dev->cmds[i].timeout = 0;
			ret = dev->cmds[i].seqno;
			break;
		}
	}
	mutex_unlock(&dev->lock);

	return ret;
}