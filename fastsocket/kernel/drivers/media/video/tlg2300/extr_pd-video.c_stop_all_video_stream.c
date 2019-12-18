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
struct video_data {struct front_face* front; scalar_t__ is_streaming; } ;
struct vbi_data {struct front_face* front; } ;
struct poseidon {int /*<<< orphan*/  lock; struct vbi_data vbi_data; struct video_data video_data; } ;
struct front_face {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_all_urb (struct video_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_transfer_stop (struct video_data*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 

int stop_all_video_stream(struct poseidon *pd)
{
	struct video_data *video = &pd->video_data;
	struct vbi_data *vbi	= &pd->vbi_data;

	mutex_lock(&pd->lock);
	if (video->is_streaming) {
		struct front_face *front = video->front;

		/* stop the URBs */
		usb_transfer_stop(video);
		free_all_urb(video);

		/* stop the host side of VIDEO */
		videobuf_stop(&front->q);
		videobuf_mmap_free(&front->q);

		/* stop the host side of VBI */
		front = vbi->front;
		if (front) {
			videobuf_stop(&front->q);
			videobuf_mmap_free(&front->q);
		}
	}
	mutex_unlock(&pd->lock);
	return 0;
}