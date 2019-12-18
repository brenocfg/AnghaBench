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
struct seq_oss_devinfo {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct seq_oss_devinfo* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 int /*<<< orphan*/  snd_seq_oss_drain_write (struct seq_oss_devinfo*) ; 
 int /*<<< orphan*/  snd_seq_oss_release (struct seq_oss_devinfo*) ; 

__attribute__((used)) static int
odev_release(struct inode *inode, struct file *file)
{
	struct seq_oss_devinfo *dp;

	if ((dp = file->private_data) == NULL)
		return 0;

	snd_seq_oss_drain_write(dp);

	mutex_lock(&register_mutex);
	snd_seq_oss_release(dp);
	mutex_unlock(&register_mutex);

	return 0;
}