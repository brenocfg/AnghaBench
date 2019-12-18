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
struct v4l2_audio {scalar_t__ index; } ;
struct file {int dummy; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {scalar_t__ ctl_ainput; } ;
struct TYPE_2__ {scalar_t__ amux; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* INPUT (scalar_t__) ; 
 int cx231xx_set_audio_input (struct cx231xx*,scalar_t__) ; 

__attribute__((used)) static int vidioc_s_audio(struct file *file, void *priv, struct v4l2_audio *a)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;
	int status = 0;

	/* Doesn't allow manual routing */
	if (a->index != dev->ctl_ainput)
		return -EINVAL;

	dev->ctl_ainput = INPUT(a->index)->amux;
	status = cx231xx_set_audio_input(dev, dev->ctl_ainput);

	return status;
}