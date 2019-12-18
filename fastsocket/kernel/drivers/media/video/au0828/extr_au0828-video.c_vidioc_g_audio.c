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
struct v4l2_audio {unsigned int index; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct au0828_fh {struct au0828_dev* dev; } ;
struct au0828_dev {unsigned int ctrl_ainput; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vidioc_g_audio(struct file *file, void *priv, struct v4l2_audio *a)
{
	struct au0828_fh *fh = priv;
	struct au0828_dev *dev = fh->dev;
	unsigned int index = a->index;

	if (a->index > 1)
		return -EINVAL;

	index = dev->ctrl_ainput;
	if (index == 0)
		strcpy(a->name, "Television");
	else
		strcpy(a->name, "Line in");

	a->capability = V4L2_AUDCAP_STEREO;
	a->index = index;
	return 0;
}