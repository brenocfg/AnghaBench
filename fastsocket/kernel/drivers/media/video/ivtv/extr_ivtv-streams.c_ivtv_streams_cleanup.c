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
struct ivtv {TYPE_1__* streams; } ;
struct TYPE_2__ {struct video_device* vdev; } ;

/* Variables and functions */
 int IVTV_MAX_STREAMS ; 
 int /*<<< orphan*/  ivtv_stream_free (TYPE_1__*) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

void ivtv_streams_cleanup(struct ivtv *itv, int unregister)
{
	int type;

	/* Teardown all streams */
	for (type = 0; type < IVTV_MAX_STREAMS; type++) {
		struct video_device *vdev = itv->streams[type].vdev;

		itv->streams[type].vdev = NULL;
		if (vdev == NULL)
			continue;

		ivtv_stream_free(&itv->streams[type]);
		/* Unregister or release device */
		if (unregister)
			video_unregister_device(vdev);
		else
			video_device_release(vdev);
	}
}