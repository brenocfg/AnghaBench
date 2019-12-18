#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_13__ {TYPE_5__ pix; } ;
struct v4l2_format {TYPE_6__ fmt; } ;
struct cpia2_fh {int /*<<< orphan*/  prio; } ;
struct TYPE_10__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_8__ {scalar_t__ inhibit_htables; } ;
struct TYPE_11__ {TYPE_3__ roi; TYPE_1__ compression; } ;
struct TYPE_9__ {scalar_t__ width; scalar_t__ height; } ;
struct camera_data {int num_frames; TYPE_7__* buffers; TYPE_4__ params; TYPE_2__ vw; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  prio; } ;
struct TYPE_14__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ FRAME_EMPTY ; 
 scalar_t__ FRAME_READING ; 
 int /*<<< orphan*/  V4L2_PRIORITY_RECORD ; 
 int /*<<< orphan*/  cpia2_set_format (struct camera_data*) ; 
 int ioctl_try_fmt (void*,struct camera_data*) ; 
 int sync (struct camera_data*,int) ; 
 int v4l2_prio_change (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_set_fmt(void *arg,struct camera_data *cam, struct cpia2_fh *fh)
{
	struct v4l2_format *f = arg;
	int err, frame;

	err = ioctl_try_fmt(arg, cam);
	if(err != 0)
		return err;

	/* Ensure that only this process can change the format. */
	err = v4l2_prio_change(&cam->prio, &fh->prio, V4L2_PRIORITY_RECORD);
	if(err != 0) {
		return err;
	}

	cam->pixelformat = f->fmt.pix.pixelformat;

	/* NOTE: This should be set to 1 for MJPEG, but some apps don't handle
	 * the missing Huffman table properly. */
	cam->params.compression.inhibit_htables = 0;
		/*f->fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG;*/

	/* we set the video window to something smaller or equal to what
	 * is requested by the user???
	 */
	DBG("Requested width = %d, height = %d\n",
	    f->fmt.pix.width, f->fmt.pix.height);
	if (f->fmt.pix.width != cam->vw.width ||
	    f->fmt.pix.height != cam->vw.height) {
		cam->vw.width = f->fmt.pix.width;
		cam->vw.height = f->fmt.pix.height;
		cam->params.roi.width = f->fmt.pix.width;
		cam->params.roi.height = f->fmt.pix.height;
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