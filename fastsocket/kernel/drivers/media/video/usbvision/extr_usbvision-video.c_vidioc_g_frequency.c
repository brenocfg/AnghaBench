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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; scalar_t__ tuner; } ;
struct usb_usbvision {int /*<<< orphan*/  freq; scalar_t__ radio; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
				struct v4l2_frequency *freq)
{
	struct usb_usbvision *usbvision = video_drvdata(file);

	freq->tuner = 0; /* Only one tuner */
	if (usbvision->radio)
		freq->type = V4L2_TUNER_RADIO;
	else
		freq->type = V4L2_TUNER_ANALOG_TV;
	freq->frequency = usbvision->freq;

	return 0;
}