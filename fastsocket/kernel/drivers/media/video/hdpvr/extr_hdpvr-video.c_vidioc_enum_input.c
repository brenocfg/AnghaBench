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
struct v4l2_input {unsigned int index; char* name; int audioset; int /*<<< orphan*/  std; int /*<<< orphan*/  type; } ;
struct hdpvr_fh {struct hdpvr_device* dev; } ;
struct hdpvr_device {TYPE_1__* video_dev; } ;
struct file {struct hdpvr_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tvnorms; } ;

/* Variables and functions */
 int EINVAL ; 
 int HDPVR_RCA_BACK ; 
 int HDPVR_RCA_FRONT ; 
 int HDPVR_SPDIF ; 
 unsigned int HDPVR_VIDEO_INPUTS ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/ * iname ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *i)
{
	struct hdpvr_fh *fh = file->private_data;
	struct hdpvr_device *dev = fh->dev;
	unsigned int n;

	n = i->index;
	if (n >= HDPVR_VIDEO_INPUTS)
		return -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;

	strncpy(i->name, iname[n], sizeof(i->name) - 1);
	i->name[sizeof(i->name) - 1] = '\0';

	i->audioset = 1<<HDPVR_RCA_FRONT | 1<<HDPVR_RCA_BACK | 1<<HDPVR_SPDIF;

	i->std = dev->video_dev->tvnorms;

	return 0;
}