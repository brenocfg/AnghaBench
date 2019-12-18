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
struct hdpvr_video_info {int width; int height; int fps; } ;
struct hdpvr_device {int* usbc_buf; int /*<<< orphan*/  usbc_mutex; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  print_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MSG_INFO ; 
 int hdpvr_debug ; 
 int /*<<< orphan*/  hex_dump_to_buffer (int*,int,int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hdpvr_video_info*) ; 
 struct hdpvr_video_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int,int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

struct hdpvr_video_info *get_video_info(struct hdpvr_device *dev)
{
	struct hdpvr_video_info *vidinf = NULL;
#ifdef HDPVR_DEBUG
	char print_buf[15];
#endif
	int ret;

	vidinf = kzalloc(sizeof(struct hdpvr_video_info), GFP_KERNEL);
	if (!vidinf) {
		v4l2_err(&dev->v4l2_dev, "out of memory\n");
		goto err;
	}

	mutex_lock(&dev->usbc_mutex);
	ret = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      0x81, 0x80 | 0x38,
			      0x1400, 0x0003,
			      dev->usbc_buf, 5,
			      1000);
	if (ret == 5) {
		vidinf->width	= dev->usbc_buf[1] << 8 | dev->usbc_buf[0];
		vidinf->height	= dev->usbc_buf[3] << 8 | dev->usbc_buf[2];
		vidinf->fps	= dev->usbc_buf[4];
	}

#ifdef HDPVR_DEBUG
	if (hdpvr_debug & MSG_INFO) {
		hex_dump_to_buffer(dev->usbc_buf, 5, 16, 1, print_buf,
				   sizeof(print_buf), 0);
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			 "get video info returned: %d, %s\n", ret, print_buf);
	}
#endif
	mutex_unlock(&dev->usbc_mutex);

	if (!vidinf->width || !vidinf->height || !vidinf->fps) {
		kfree(vidinf);
		vidinf = NULL;
	}
err:
	return vidinf;
}