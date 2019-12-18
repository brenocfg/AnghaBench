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
struct btrfs_root {int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  log_writers; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int btrfs_pin_log_trans(struct btrfs_root *root)
{
	int ret = -ENOENT;

	mutex_lock(&root->log_mutex);
	atomic_inc(&root->log_writers);
	mutex_unlock(&root->log_mutex);
	return ret;
}