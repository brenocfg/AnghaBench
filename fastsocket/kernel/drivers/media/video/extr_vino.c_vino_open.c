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
struct vino_channel_settings {scalar_t__ channel; int /*<<< orphan*/  mutex; scalar_t__ users; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ VINO_CHANNEL_A ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 int vino_acquire_input (struct vino_channel_settings*) ; 

__attribute__((used)) static int vino_open(struct file *file)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	int ret = 0;
	dprintk("open(): channel = %c\n",
	       (vcs->channel == VINO_CHANNEL_A) ? 'A' : 'B');

	mutex_lock(&vcs->mutex);

	if (vcs->users) {
		dprintk("open(): driver busy\n");
		ret = -EBUSY;
		goto out;
	}

	ret = vino_acquire_input(vcs);
	if (ret) {
		dprintk("open(): vino_acquire_input() failed\n");
		goto out;
	}

	vcs->users++;

 out:
	mutex_unlock(&vcs->mutex);

	dprintk("open(): %s!\n", ret ? "failed" : "complete");

	return ret;
}