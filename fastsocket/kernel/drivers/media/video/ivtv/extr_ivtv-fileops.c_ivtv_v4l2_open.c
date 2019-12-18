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
struct ivtv_stream {struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  serialize_lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IVTV_ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ivtv_init_on_first_open (struct ivtv*) ; 
 int ivtv_serialized_open (struct ivtv_stream*,struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct ivtv_stream* video_get_drvdata (struct video_device*) ; 

int ivtv_v4l2_open(struct file *filp)
{
	int res;
	struct ivtv *itv = NULL;
	struct ivtv_stream *s = NULL;
	struct video_device *vdev = video_devdata(filp);

	s = video_get_drvdata(vdev);
	itv = s->itv;

	mutex_lock(&itv->serialize_lock);
	if (ivtv_init_on_first_open(itv)) {
		IVTV_ERR("Failed to initialize on device %s\n",
			 video_device_node_name(vdev));
		mutex_unlock(&itv->serialize_lock);
		return -ENXIO;
	}
	res = ivtv_serialized_open(s, filp);
	mutex_unlock(&itv->serialize_lock);
	return res;
}