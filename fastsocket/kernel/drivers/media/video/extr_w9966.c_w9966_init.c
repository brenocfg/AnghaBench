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
struct w9966_dev {scalar_t__ dev_state; int brightness; int contrast; int color; struct parport* pport; int /*<<< orphan*/  vdev; int /*<<< orphan*/ * pdev; void* ppmode; scalar_t__ hue; } ;
struct video_device {int dummy; } ;
struct parport {int modes; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 void* IEEE1284_MODE_ECP ; 
 void* IEEE1284_MODE_EPP ; 
 int PARPORT_MODE_ECP ; 
 int PARPORT_MODE_EPP ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  W9966_STATE_PDEV ; 
 int /*<<< orphan*/  W9966_STATE_VDEV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int parmode ; 
 int /*<<< orphan*/ * parport_register_device (struct parport*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_nr ; 
 scalar_t__ video_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (int /*<<< orphan*/ *,struct w9966_dev*) ; 
 int /*<<< orphan*/  w9966_pdev_claim (struct w9966_dev*) ; 
 int /*<<< orphan*/  w9966_pdev_release (struct w9966_dev*) ; 
 int /*<<< orphan*/  w9966_setState (struct w9966_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ w9966_setup (struct w9966_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  w9966_template ; 

__attribute__((used)) static int w9966_init(struct w9966_dev* cam, struct parport* port)
{
	if (cam->dev_state != 0)
		return -1;

	cam->pport = port;
	cam->brightness = 128;
	cam->contrast = 64;
	cam->color = 64;
	cam->hue = 0;

// Select requested transfer mode
	switch(parmode)
	{
	default:	// Auto-detect (priority: hw-ecp, hw-epp, sw-ecp)
	case 0:
		if (port->modes & PARPORT_MODE_ECP)
			cam->ppmode = IEEE1284_MODE_ECP;
		else if (port->modes & PARPORT_MODE_EPP)
			cam->ppmode = IEEE1284_MODE_EPP;
		else
			cam->ppmode = IEEE1284_MODE_ECP;
		break;
	case 1:		// hw- or sw-ecp
		cam->ppmode = IEEE1284_MODE_ECP;
		break;
	case 2:		// hw- or sw-epp
		cam->ppmode = IEEE1284_MODE_EPP;
	break;
	}

// Tell the parport driver that we exists
	cam->pdev = parport_register_device(port, "w9966", NULL, NULL, NULL, 0, NULL);
	if (cam->pdev == NULL) {
		DPRINTF("parport_register_device() failed\n");
		return -1;
	}
	w9966_setState(cam, W9966_STATE_PDEV, W9966_STATE_PDEV);

	w9966_pdev_claim(cam);

// Setup a default capture mode
	if (w9966_setup(cam, 0, 0, 1023, 1023, 200, 160) != 0) {
		DPRINTF("w9966_setup() failed.\n");
		return -1;
	}

	w9966_pdev_release(cam);

// Fill in the video_device struct and register us to v4l
	memcpy(&cam->vdev, &w9966_template, sizeof(struct video_device));
	video_set_drvdata(&cam->vdev, cam);

	if (video_register_device(&cam->vdev, VFL_TYPE_GRABBER, video_nr) < 0)
		return -1;

	w9966_setState(cam, W9966_STATE_VDEV, W9966_STATE_VDEV);

	// All ok
	printk(
		"w9966cf: Found and initialized a webcam on %s.\n",
		cam->pport->name
	);
	return 0;
}