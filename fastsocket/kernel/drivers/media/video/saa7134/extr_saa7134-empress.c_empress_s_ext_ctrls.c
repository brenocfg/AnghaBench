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
struct v4l2_ext_controls {scalar_t__ count; scalar_t__ ctrl_class; } ;
struct saa7134_dev {int dummy; } ;
struct file {struct saa7134_dev* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_CLASS_MPEG ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  s_ext_ctrls ; 
 int saa_call_empress (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_ext_controls*) ; 
 int /*<<< orphan*/  ts_init_encoder (struct saa7134_dev*) ; 

__attribute__((used)) static int empress_s_ext_ctrls(struct file *file, void *priv,
			       struct v4l2_ext_controls *ctrls)
{
	struct saa7134_dev *dev = file->private_data;
	int err;

	/* count == 0 is abused in saa6752hs.c, so that special
		case is handled here explicitly. */
	if (ctrls->count == 0)
		return 0;

	if (ctrls->ctrl_class != V4L2_CTRL_CLASS_MPEG)
		return -EINVAL;

	err = saa_call_empress(dev, core, s_ext_ctrls, ctrls);
	ts_init_encoder(dev);

	return err;
}