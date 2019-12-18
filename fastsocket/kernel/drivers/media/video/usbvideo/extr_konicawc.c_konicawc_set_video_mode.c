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
struct video_window {int width; int height; int flags; } ;
struct uvd {int ifaceAltActive; int curframe; TYPE_1__* frame; int /*<<< orphan*/  dp; scalar_t__ user_data; } ;
struct konicawc {int speed; int size; int lastframe; } ;
struct TYPE_4__ {int width; int height; } ;
struct TYPE_3__ {scalar_t__ seqRead_Index; scalar_t__ seqRead_Length; scalar_t__ curline; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 int EINVAL ; 
 int MAX_FRAME_SIZE ; 
 int MAX_SPEED ; 
 int /*<<< orphan*/  RingQueue_Flush (int /*<<< orphan*/ *) ; 
 TYPE_2__* camera_sizes ; 
 int konicawc_find_fps (int,int) ; 
 int /*<<< orphan*/  konicawc_set_camera_size (struct uvd*) ; 
 int /*<<< orphan*/  konicawc_start_data (struct uvd*) ; 
 int /*<<< orphan*/  konicawc_stop_data (struct uvd*) ; 
 int** spd_to_fps ; 
 int* spd_to_iface ; 

__attribute__((used)) static int konicawc_set_video_mode(struct uvd *uvd, struct video_window *vw)
{
	struct konicawc *cam = (struct konicawc *)uvd->user_data;
	int newspeed = cam->speed;
	int newsize;
	int x = vw->width;
	int y = vw->height;
	int fps = vw->flags;

	if(x > 0 && y > 0) {
		DEBUG(2, "trying to find size %d,%d", x, y);
		for(newsize = 0; newsize <= MAX_FRAME_SIZE; newsize++) {
			if((camera_sizes[newsize].width == x) && (camera_sizes[newsize].height == y))
				break;
		}
	} else {
		newsize = cam->size;
	}

	if(newsize > MAX_FRAME_SIZE) {
		DEBUG(1, "couldn't find size %d,%d", x, y);
		return -EINVAL;
	}

	if(fps > 0) {
		DEBUG(1, "trying to set fps to %d", fps);
		newspeed = konicawc_find_fps(newsize, fps);
		DEBUG(1, "find_fps returned %d (%d)", newspeed, spd_to_fps[newsize][newspeed]);
	}

	if(newspeed > MAX_SPEED)
		return -EINVAL;

	DEBUG(1, "setting size to %d speed to %d", newsize, newspeed);
	if((newsize == cam->size) && (newspeed == cam->speed)) {
		DEBUG(1, "Nothing to do");
		return 0;
	}
	DEBUG(0, "setting to  %dx%d @ %d fps", camera_sizes[newsize].width,
	     camera_sizes[newsize].height, spd_to_fps[newsize][newspeed]/3);

	konicawc_stop_data(uvd);
	uvd->ifaceAltActive = spd_to_iface[newspeed];
	DEBUG(1, "new interface = %d", uvd->ifaceAltActive);
	cam->speed = newspeed;

	if(cam->size != newsize) {
		cam->size = newsize;
		konicawc_set_camera_size(uvd);
	}

	/* Flush the input queue and clear any current frame in progress */

	RingQueue_Flush(&uvd->dp);
	cam->lastframe = -2;
	if(uvd->curframe != -1) {
		uvd->frame[uvd->curframe].curline = 0;
		uvd->frame[uvd->curframe].seqRead_Length = 0;
		uvd->frame[uvd->curframe].seqRead_Index = 0;
	}

	konicawc_start_data(uvd);
	return 0;
}