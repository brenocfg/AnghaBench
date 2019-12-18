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
struct v4l2_querymenu {int /*<<< orphan*/  id; } ;
struct saa7134_dev {int dummy; } ;
struct file {struct saa7134_dev* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_CLASS_MPEG ; 
 scalar_t__ V4L2_CTRL_ID2CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  querymenu ; 
 int saa_call_empress (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_querymenu*) ; 

__attribute__((used)) static int empress_querymenu(struct file *file, void *priv,
					struct v4l2_querymenu *c)
{
	struct saa7134_dev *dev = file->private_data;

	if (V4L2_CTRL_ID2CLASS(c->id) != V4L2_CTRL_CLASS_MPEG)
		return -EINVAL;
	return saa_call_empress(dev, core, querymenu, c);
}