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
struct v4l2_audio {int /*<<< orphan*/  capability; int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int /*<<< orphan*/  ctl_ainput; } ;

/* Variables and functions */
#define  CX231XX_AMUX_LINE_IN 129 
#define  CX231XX_AMUX_VIDEO 128 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vidioc_g_audio(struct file *file, void *priv, struct v4l2_audio *a)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;

	switch (a->index) {
	case CX231XX_AMUX_VIDEO:
		strcpy(a->name, "Television");
		break;
	case CX231XX_AMUX_LINE_IN:
		strcpy(a->name, "Line In");
		break;
	default:
		return -EINVAL;
	}

	a->index = dev->ctl_ainput;
	a->capability = V4L2_AUDCAP_STEREO;

	return 0;
}