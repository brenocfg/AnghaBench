#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct video_window {scalar_t__ clipcount; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/ * clips; } ;
struct cpia2_fh {int /*<<< orphan*/  prio; } ;
struct TYPE_8__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_6__ {scalar_t__ inhibit_htables; } ;
struct TYPE_9__ {TYPE_3__ roi; TYPE_1__ compression; } ;
struct TYPE_7__ {scalar_t__ width; scalar_t__ height; } ;
struct camera_data {int num_frames; TYPE_5__* buffers; TYPE_4__ params; TYPE_2__ vw; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  prio; } ;
struct TYPE_10__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ FRAME_EMPTY ; 
 scalar_t__ FRAME_READING ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  V4L2_PRIORITY_RECORD ; 
 int /*<<< orphan*/  cpia2_set_format (struct camera_data*) ; 
 int sync (struct camera_data*,int) ; 
 int v4l2_prio_change (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_set_window_size(void *arg, struct camera_data *cam,
				 struct cpia2_fh *fh)
{
	/* copy_from_user, check validity, copy to internal structure */
	struct video_window *vw;
	int frame, err;
	vw = arg;

	if (vw->clipcount != 0)	/* clipping not supported */
		return -EINVAL;

	if (vw->clips != NULL)	/* clipping not supported */
		return -EINVAL;

	/* Ensure that only this process can change the format. */
	err = v4l2_prio_change(&cam->prio, &fh->prio, V4L2_PRIORITY_RECORD);
	if(err != 0)
		return err;

	cam->pixelformat = V4L2_PIX_FMT_JPEG;

	/* Be sure to supply the Huffman tables, this isn't MJPEG */
	cam->params.compression.inhibit_htables = 0;

	/* we set the video window to something smaller or equal to what
	 * is requested by the user???
	 */
	DBG("Requested width = %d, height = %d\n", vw->width, vw->height);
	if (vw->width != cam->vw.width || vw->height != cam->vw.height) {
		cam->vw.width = vw->width;
		cam->vw.height = vw->height;
		cam->params.roi.width = vw->width;
		cam->params.roi.height = vw->height;
		cpia2_set_format(cam);
	}

	for (frame = 0; frame < cam->num_frames; ++frame) {
		if (cam->buffers[frame].status == FRAME_READING)
			if ((err = sync(cam, frame)) < 0)
				return err;

		cam->buffers[frame].status = FRAME_EMPTY;
	}

	return 0;
}