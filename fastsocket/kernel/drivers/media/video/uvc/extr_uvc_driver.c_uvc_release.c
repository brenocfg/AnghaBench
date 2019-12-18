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
struct video_device {int dummy; } ;
struct uvc_streaming {struct uvc_device* dev; } ;
struct uvc_device {int /*<<< orphan*/  nstreams; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_delete (struct uvc_device*) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 struct uvc_streaming* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void uvc_release(struct video_device *vdev)
{
	struct uvc_streaming *stream = video_get_drvdata(vdev);
	struct uvc_device *dev = stream->dev;

	video_device_release(vdev);

	/* Decrement the registered streams count and delete the device when it
	 * reaches zero.
	 */
	if (atomic_dec_and_test(&dev->nstreams))
		uvc_delete(dev);
}