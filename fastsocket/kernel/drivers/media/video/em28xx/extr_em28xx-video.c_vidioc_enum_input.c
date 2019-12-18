#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_input {unsigned int index; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct em28xx_fh {struct em28xx* dev; } ;
struct em28xx {TYPE_1__* vdev; } ;
struct TYPE_4__ {size_t type; } ;
struct TYPE_3__ {int /*<<< orphan*/  tvnorms; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t EM28XX_VMUX_CABLE ; 
 size_t EM28XX_VMUX_TELEVISION ; 
 TYPE_2__* INPUT (unsigned int) ; 
 unsigned int MAX_EM28XX_INPUT ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/ * iname ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *i)
{
	struct em28xx_fh   *fh  = priv;
	struct em28xx      *dev = fh->dev;
	unsigned int       n;

	n = i->index;
	if (n >= MAX_EM28XX_INPUT)
		return -EINVAL;
	if (0 == INPUT(n)->type)
		return -EINVAL;

	i->index = n;
	i->type = V4L2_INPUT_TYPE_CAMERA;

	strcpy(i->name, iname[INPUT(n)->type]);

	if ((EM28XX_VMUX_TELEVISION == INPUT(n)->type) ||
		(EM28XX_VMUX_CABLE == INPUT(n)->type))
		i->type = V4L2_INPUT_TYPE_TUNER;

	i->std = dev->vdev->tvnorms;

	return 0;
}