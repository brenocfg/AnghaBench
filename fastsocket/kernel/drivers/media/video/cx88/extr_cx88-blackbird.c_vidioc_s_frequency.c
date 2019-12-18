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
struct v4l2_frequency {int dummy; } ;
struct file {int dummy; } ;
struct cx88_core {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  field; } ;
struct cx8802_fh {TYPE_1__ mpegq; struct cx8802_dev* dev; } ;
struct cx8802_dev {int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct cx88_core* core; scalar_t__ mpeg_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  blackbird_initialize_codec (struct cx8802_dev*) ; 
 int /*<<< orphan*/  blackbird_stop_codec (struct cx8802_dev*) ; 
 int /*<<< orphan*/  cx88_set_freq (struct cx88_core*,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  cx88_set_scale (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_frequency (struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct cx8802_fh  *fh   = priv;
	struct cx8802_dev *dev  = fh->dev;
	struct cx88_core  *core = dev->core;

	if (dev->mpeg_active)
		blackbird_stop_codec(dev);

	cx88_set_freq (core,f);
	blackbird_initialize_codec(dev);
	cx88_set_scale(dev->core, dev->width, dev->height,
			fh->mpegq.field);
	return 0;
}