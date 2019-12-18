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
struct cx8802_dev {int /*<<< orphan*/ * mpeg_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blackbird_unregister_video(struct cx8802_dev *dev)
{
	if (dev->mpeg_dev) {
		if (video_is_registered(dev->mpeg_dev))
			video_unregister_device(dev->mpeg_dev);
		else
			video_device_release(dev->mpeg_dev);
		dev->mpeg_dev = NULL;
	}
}