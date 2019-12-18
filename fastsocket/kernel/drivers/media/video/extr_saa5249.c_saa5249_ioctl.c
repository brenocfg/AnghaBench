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
struct saa5249_device {int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_saa5249_ioctl ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct saa5249_device* video_drvdata (struct file*) ; 
 long video_usercopy (struct file*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned int vtx_fix_command (unsigned int) ; 

__attribute__((used)) static long saa5249_ioctl(struct file *file,
			 unsigned int cmd, unsigned long arg)
{
	struct saa5249_device *t = video_drvdata(file);
	long err;

	cmd = vtx_fix_command(cmd);
	mutex_lock(&t->lock);
	err = video_usercopy(file, cmd, arg, do_saa5249_ioctl);
	mutex_unlock(&t->lock);
	return err;
}