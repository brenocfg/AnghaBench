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
struct hdpvr_fh {struct hdpvr_device* dev; } ;
struct TYPE_2__ {unsigned int video_input; } ;
struct hdpvr_device {scalar_t__ status; TYPE_1__ options; } ;
struct file {struct hdpvr_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_VIDEO_INPUT_VALUE ; 
 int EAGAIN ; 
 int EINVAL ; 
 unsigned int HDPVR_VIDEO_INPUTS ; 
 scalar_t__ STATUS_IDLE ; 
 int hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *private_data,
			  unsigned int index)
{
	struct hdpvr_fh *fh = file->private_data;
	struct hdpvr_device *dev = fh->dev;
	int retval;

	if (index >= HDPVR_VIDEO_INPUTS)
		return -EINVAL;

	if (dev->status != STATUS_IDLE)
		return -EAGAIN;

	retval = hdpvr_config_call(dev, CTRL_VIDEO_INPUT_VALUE, index+1);
	if (!retval)
		dev->options.video_input = index;

	return retval;
}