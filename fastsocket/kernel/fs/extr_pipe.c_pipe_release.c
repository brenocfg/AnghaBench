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
struct pipe_inode_info {int /*<<< orphan*/  fasync_writers; int /*<<< orphan*/  fasync_readers; int /*<<< orphan*/  wait; scalar_t__ writers; scalar_t__ readers; } ;
struct inode {int /*<<< orphan*/  i_mutex; struct pipe_inode_info* i_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  free_pipe_info (struct inode*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pipe_release(struct inode *inode, int decr, int decw)
{
	struct pipe_inode_info *pipe;

	mutex_lock(&inode->i_mutex);
	pipe = inode->i_pipe;
	pipe->readers -= decr;
	pipe->writers -= decw;

	if (!pipe->readers && !pipe->writers) {
		free_pipe_info(inode);
	} else {
		wake_up_interruptible_sync(&pipe->wait);
		kill_fasync(&pipe->fasync_readers, SIGIO, POLL_IN);
		kill_fasync(&pipe->fasync_writers, SIGIO, POLL_OUT);
	}
	mutex_unlock(&inode->i_mutex);

	return 0;
}