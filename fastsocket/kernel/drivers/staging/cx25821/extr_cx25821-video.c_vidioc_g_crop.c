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
struct v4l2_crop {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int vidioc_g_crop(struct file *file, void *priv, struct v4l2_crop *crop)
{
	// vidioc_g_crop not supported
	return -EINVAL;
}