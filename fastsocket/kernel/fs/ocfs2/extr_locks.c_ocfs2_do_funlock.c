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
struct ocfs2_file_private {int /*<<< orphan*/  fp_mutex; } ;
struct file_lock {int dummy; } ;
struct file {struct ocfs2_file_private* private_data; } ;

/* Variables and functions */
 int flock_lock_file_wait (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_file_unlock (struct file*) ; 

__attribute__((used)) static int ocfs2_do_funlock(struct file *file, int cmd, struct file_lock *fl)
{
	int ret;
	struct ocfs2_file_private *fp = file->private_data;

	mutex_lock(&fp->fp_mutex);
	ocfs2_file_unlock(file);
	ret = flock_lock_file_wait(file, fl);
	mutex_unlock(&fp->fp_mutex);

	return ret;
}