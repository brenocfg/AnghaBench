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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct usb_usbvision {int /*<<< orphan*/  ctl_input; int /*<<< orphan*/  tvnorm_id; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_all (struct usb_usbvision*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  usbvision_muxsel (struct usb_usbvision*,int /*<<< orphan*/ ) ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id *id)
{
	struct usb_usbvision *usbvision = video_drvdata(file);

	usbvision->tvnorm_id = *id;

	call_all(usbvision, core, s_std, usbvision->tvnorm_id);
	/* propagate the change to the decoder */
	usbvision_muxsel(usbvision, usbvision->ctl_input);

	return 0;
}