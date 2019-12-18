#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_window {int width; int height; } ;
struct uvd {int curframe; TYPE_1__* frame; int /*<<< orphan*/  dp; scalar_t__ user_data; } ;
struct qcm {int size; } ;
struct TYPE_4__ {int width; int height; } ;
struct TYPE_3__ {scalar_t__ seqRead_Index; scalar_t__ seqRead_Length; scalar_t__ curline; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 int EINVAL ; 
 int MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  RingQueue_Flush (int /*<<< orphan*/ *) ; 
 TYPE_2__* camera_sizes ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int qcm_set_camera_size (struct uvd*) ; 
 int /*<<< orphan*/  qcm_start_data (struct uvd*) ; 
 int /*<<< orphan*/  qcm_stop_data (struct uvd*) ; 

__attribute__((used)) static int qcm_set_video_mode(struct uvd *uvd, struct video_window *vw)
{
	int ret;
	int newsize;
	int oldsize;
	int x = vw->width;
	int y = vw->height;
	struct qcm *cam = (struct qcm *) uvd->user_data;

	if (x > 0 && y > 0) {
		DEBUG(2, "trying to find size %d,%d", x, y);
		for (newsize = 0; newsize <= MAX_FRAME_SIZE; newsize++) {
			if ((camera_sizes[newsize].width == x) &&
				(camera_sizes[newsize].height == y))
				break;
		}
	} else
		newsize = cam->size;

	if (newsize > MAX_FRAME_SIZE) {
		DEBUG(1, "couldn't find size %d,%d", x, y);
		return -EINVAL;
	}

	if (newsize == cam->size) {
		DEBUG(1, "Nothing to do");
		return 0;
	}

	qcm_stop_data(uvd);

	if (cam->size != newsize) {
		oldsize = cam->size;
		cam->size = newsize;
		ret = qcm_set_camera_size(uvd);
		if (ret) {
			err("Couldn't set camera size, err=%d",ret);
			/* restore the original size */
			cam->size = oldsize;
			return ret;
		}
	}

	/* Flush the input queue and clear any current frame in progress */

	RingQueue_Flush(&uvd->dp);
	if (uvd->curframe != -1) {
		uvd->frame[uvd->curframe].curline = 0;
		uvd->frame[uvd->curframe].seqRead_Length = 0;
		uvd->frame[uvd->curframe].seqRead_Index = 0;
	}

	CHECK_RET(ret, qcm_start_data(uvd));
	return 0;
}