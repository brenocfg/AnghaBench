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
struct bttv {int /*<<< orphan*/ * radio_dev; int /*<<< orphan*/ * vbi_dev; int /*<<< orphan*/ * video_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bttv_unregister_video(struct bttv *btv)
{
	if (btv->video_dev) {
		if (video_is_registered(btv->video_dev))
			video_unregister_device(btv->video_dev);
		else
			video_device_release(btv->video_dev);
		btv->video_dev = NULL;
	}
	if (btv->vbi_dev) {
		if (video_is_registered(btv->vbi_dev))
			video_unregister_device(btv->vbi_dev);
		else
			video_device_release(btv->vbi_dev);
		btv->vbi_dev = NULL;
	}
	if (btv->radio_dev) {
		if (video_is_registered(btv->radio_dev))
			video_unregister_device(btv->radio_dev);
		else
			video_device_release(btv->radio_dev);
		btv->radio_dev = NULL;
	}
}