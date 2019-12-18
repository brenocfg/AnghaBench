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
 int /*<<< orphan*/  pvr2_v4l2_do_ioctl ; 
 long video_usercopy (struct file*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long pvr2_v4l2_ioctl(struct file *file,
			   unsigned int cmd, unsigned long arg)
{

	return video_usercopy(file, cmd, arg, pvr2_v4l2_do_ioctl);
}