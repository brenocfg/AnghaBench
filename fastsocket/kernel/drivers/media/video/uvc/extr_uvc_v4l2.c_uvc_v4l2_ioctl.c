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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int UVC_TRACE_IOCTL ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  uvc_printk (int /*<<< orphan*/ ,char*) ; 
 int uvc_trace_param ; 
 int /*<<< orphan*/  uvc_v4l2_do_ioctl ; 
 int /*<<< orphan*/  v4l_printk_ioctl (unsigned int) ; 
 long video_usercopy (struct file*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long uvc_v4l2_ioctl(struct file *file,
		     unsigned int cmd, unsigned long arg)
{
	if (uvc_trace_param & UVC_TRACE_IOCTL) {
		uvc_printk(KERN_DEBUG, "uvc_v4l2_ioctl(");
		v4l_printk_ioctl(cmd);
		printk(")\n");
	}

	return video_usercopy(file, cmd, arg, uvc_v4l2_do_ioctl);
}