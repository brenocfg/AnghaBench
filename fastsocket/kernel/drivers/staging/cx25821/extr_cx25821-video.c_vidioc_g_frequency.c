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
struct v4l2_frequency {int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;
struct cx25821_fh {struct cx25821_dev* dev; } ;
struct cx25821_dev {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25821_call_all (struct cx25821_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  tuner ; 

int vidioc_g_frequency(struct file *file, void *priv, struct v4l2_frequency *f)
{
	struct cx25821_fh *fh = priv;
	struct cx25821_dev *dev = fh->dev;

	f->frequency = dev->freq;

	cx25821_call_all(dev, tuner, g_frequency, f);

	return 0;
}