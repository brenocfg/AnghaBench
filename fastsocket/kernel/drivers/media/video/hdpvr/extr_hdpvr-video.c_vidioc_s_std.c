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
typedef  int v4l2_std_id ;
typedef  int u8 ;
struct hdpvr_fh {struct hdpvr_device* dev; } ;
struct hdpvr_device {int dummy; } ;
struct file {struct hdpvr_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_VIDEO_STD_TYPE ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL_60 ; 
 int hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *private_data,
			v4l2_std_id *std)
{
	struct hdpvr_fh *fh = file->private_data;
	struct hdpvr_device *dev = fh->dev;
	u8 std_type = 1;

	if (*std & (V4L2_STD_NTSC | V4L2_STD_PAL_60))
		std_type = 0;

	return hdpvr_config_call(dev, CTRL_VIDEO_STD_TYPE, std_type);
}