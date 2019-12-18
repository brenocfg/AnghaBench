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
struct uvc_streaming {int /*<<< orphan*/  chain; TYPE_1__* dev; } ;
struct uvc_fh {int /*<<< orphan*/  state; struct uvc_streaming* stream; int /*<<< orphan*/  chain; } ;
struct file {struct uvc_fh* private_data; } ;
struct TYPE_2__ {int state; int /*<<< orphan*/  users; int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UVC_DEV_DISCONNECTED ; 
 int /*<<< orphan*/  UVC_HANDLE_PASSIVE ; 
 int /*<<< orphan*/  UVC_TRACE_CALLS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct uvc_fh*) ; 
 struct uvc_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int uvc_status_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 
 struct uvc_streaming* video_drvdata (struct file*) ; 

__attribute__((used)) static int uvc_v4l2_open(struct file *file)
{
	struct uvc_streaming *stream;
	struct uvc_fh *handle;
	int ret = 0;

	uvc_trace(UVC_TRACE_CALLS, "uvc_v4l2_open\n");
	stream = video_drvdata(file);

	if (stream->dev->state & UVC_DEV_DISCONNECTED)
		return -ENODEV;

	ret = usb_autopm_get_interface(stream->dev->intf);
	if (ret < 0)
		return ret;

	/* Create the device handle. */
	handle = kzalloc(sizeof *handle, GFP_KERNEL);
	if (handle == NULL) {
		usb_autopm_put_interface(stream->dev->intf);
		return -ENOMEM;
	}

	if (atomic_inc_return(&stream->dev->users) == 1) {
		ret = uvc_status_start(stream->dev);
		if (ret < 0) {
			usb_autopm_put_interface(stream->dev->intf);
			atomic_dec(&stream->dev->users);
			kfree(handle);
			return ret;
		}
	}

	handle->chain = stream->chain;
	handle->stream = stream;
	handle->state = UVC_HANDLE_PASSIVE;
	file->private_data = handle;

	return 0;
}