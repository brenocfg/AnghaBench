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
struct video_device {int dummy; } ;
struct pwc_device {int vframe_count; int /*<<< orphan*/  modlock; struct video_device* vopen; int /*<<< orphan*/  unplugged; int /*<<< orphan*/  type; int /*<<< orphan*/  vframes_error; int /*<<< orphan*/  vframes_dumped; } ;
struct file {struct video_device* private_data; } ;
struct TYPE_2__ {struct pwc_device* pdev; } ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC1 (int /*<<< orphan*/ ) ; 
 int MAX_DEV_HINTS ; 
 int /*<<< orphan*/  PWC_DEBUG_MODULE (char*,...) ; 
 int /*<<< orphan*/  PWC_DEBUG_OPEN (char*,struct video_device*) ; 
 int /*<<< orphan*/  PWC_ERROR (char*,int) ; 
 TYPE_1__* device_hint ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ power_save ; 
 int pwc_camera_power (struct pwc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwc_cleanup (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_dec1_exit () ; 
 int /*<<< orphan*/  pwc_dec23_exit () ; 
 int /*<<< orphan*/  pwc_free_buffers (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_isoc_cleanup (struct pwc_device*) ; 
 scalar_t__ pwc_set_leds (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pwc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int pwc_video_close(struct file *file)
{
	struct video_device *vdev = file->private_data;
	struct pwc_device *pdev;
	int i, hint;

	PWC_DEBUG_OPEN(">> video_close called(vdev = 0x%p).\n", vdev);

	pdev = video_get_drvdata(vdev);
	mutex_lock(&pdev->modlock);
	if (pdev->vopen == 0)
		PWC_DEBUG_MODULE("video_close() called on closed device?\n");

	/* Dump statistics, but only if a reasonable amount of frames were
	   processed (to prevent endless log-entries in case of snap-shot
	   programs)
	 */
	if (pdev->vframe_count > 20)
		PWC_DEBUG_MODULE("Closing video device: %d frames received, dumped %d frames, %d frames with errors.\n", pdev->vframe_count, pdev->vframes_dumped, pdev->vframes_error);

	if (DEVICE_USE_CODEC1(pdev->type))
	    pwc_dec1_exit();
	else
	    pwc_dec23_exit();

	pwc_isoc_cleanup(pdev);
	pwc_free_buffers(pdev);

	/* Turn off LEDS and power down camera, but only when not unplugged */
	if (!pdev->unplugged) {
		/* Turn LEDs off */
		if (pwc_set_leds(pdev, 0, 0) < 0)
			PWC_DEBUG_MODULE("Failed to set LED on/off time.\n");
		if (power_save) {
			i = pwc_camera_power(pdev, 0);
			if (i < 0)
				PWC_ERROR("Failed to power down camera (%d)\n", i);
		}
		pdev->vopen--;
		PWC_DEBUG_OPEN("<< video_close() vopen=%d\n", pdev->vopen);
	} else {
		pwc_cleanup(pdev);
		/* search device_hint[] table if we occupy a slot, by any chance */
		for (hint = 0; hint < MAX_DEV_HINTS; hint++)
			if (device_hint[hint].pdev == pdev)
				device_hint[hint].pdev = NULL;
	}
	mutex_unlock(&pdev->modlock);

	return 0;
}