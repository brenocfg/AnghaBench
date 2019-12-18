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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct au0828_fh {struct au0828_dev* dev; } ;
struct au0828_dev {int /*<<< orphan*/  ctrl_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
				struct v4l2_frequency *freq)
{
	struct au0828_fh *fh = priv;
	struct au0828_dev *dev = fh->dev;

	freq->type = V4L2_TUNER_ANALOG_TV;
	freq->frequency = dev->ctrl_freq;
	return 0;
}