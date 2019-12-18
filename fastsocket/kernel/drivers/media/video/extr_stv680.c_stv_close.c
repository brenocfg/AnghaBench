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
struct usb_stv {int maxframesize; scalar_t__ removed; scalar_t__ user; int /*<<< orphan*/  fbuf; scalar_t__ streaming; TYPE_1__* frame; } ;
struct file {struct video_device* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  grabstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_UNUSED ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int STV680_NUMFRAMES ; 
 int /*<<< orphan*/  kfree (struct usb_stv*) ; 
 int /*<<< orphan*/  rvfree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv680_stop_stream (struct usb_stv*) ; 
 int stv_stop_video (struct usb_stv*) ; 
 struct usb_stv* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int stv_close(struct file *file)
{
	struct video_device *dev = file->private_data;
	struct usb_stv *stv680 = video_get_drvdata(dev);
	int i;

	for (i = 0; i < STV680_NUMFRAMES; i++)
		stv680->frame[i].grabstate = FRAME_UNUSED;
	if (stv680->streaming)
		stv680_stop_stream (stv680);

	if ((i = stv_stop_video (stv680)) < 0)
		PDEBUG (1, "STV(e): stop_video failed in stv_close");

	rvfree (stv680->fbuf, stv680->maxframesize * STV680_NUMFRAMES);
	stv680->user = 0;

	if (stv680->removed) {
		kfree(stv680);
		stv680 = NULL;
		PDEBUG (0, "STV(i): device unregistered");
	}
	file->private_data = NULL;
	return 0;
}