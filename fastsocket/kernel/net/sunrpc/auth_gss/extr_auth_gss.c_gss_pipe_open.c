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
struct inode {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_users ; 
 int pipe_version ; 
 int /*<<< orphan*/  pipe_version_lock ; 
 int /*<<< orphan*/  pipe_version_rpc_waitqueue ; 
 int /*<<< orphan*/  pipe_version_waitqueue ; 
 int /*<<< orphan*/  rpc_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gss_pipe_open(struct inode *inode, int new_version)
{
	int ret = 0;

	spin_lock(&pipe_version_lock);
	if (pipe_version < 0) {
		/* First open of any gss pipe determines the version: */
		pipe_version = new_version;
		rpc_wake_up(&pipe_version_rpc_waitqueue);
		wake_up(&pipe_version_waitqueue);
	} else if (pipe_version != new_version) {
		/* Trying to open a pipe of a different version */
		ret = -EBUSY;
		goto out;
	}
	atomic_inc(&pipe_users);
out:
	spin_unlock(&pipe_version_lock);
	return ret;

}