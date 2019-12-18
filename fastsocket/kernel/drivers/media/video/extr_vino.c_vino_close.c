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
struct vino_channel_settings {int /*<<< orphan*/  mutex; int /*<<< orphan*/  fb_queue; int /*<<< orphan*/  users; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vino_capture_stop (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vino_release_input (struct vino_channel_settings*) ; 

__attribute__((used)) static int vino_close(struct file *file)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	dprintk("close():\n");

	mutex_lock(&vcs->mutex);

	vcs->users--;

	if (!vcs->users) {
		vino_release_input(vcs);

		/* stop DMA and free buffers */
		vino_capture_stop(vcs);
		vino_queue_free(&vcs->fb_queue);
	}

	mutex_unlock(&vcs->mutex);

	return 0;
}