#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_input {int index; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {struct cx23885_fh* private_data; } ;
struct cx23885_input {scalar_t__ type; } ;
struct cx23885_fh {struct cx23885_dev* dev; } ;
struct cx23885_dev {size_t board; } ;
struct TYPE_5__ {struct cx23885_input* input; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ CX23885_VMUX_CABLE ; 
 scalar_t__ CX23885_VMUX_TELEVISION ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 TYPE_2__* cx23885_boards ; 
 TYPE_1__* cx23885_tvnorms ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *i)
{
	struct cx23885_fh  *fh  = file->private_data;
	struct cx23885_dev *dev = fh->dev;
	struct cx23885_input *input;
	int n;

	if (i->index >= 4)
		return -EINVAL;

	input = &cx23885_boards[dev->board].input[i->index];

	if (input->type == 0)
		return -EINVAL;

	/* FIXME
	 * strcpy(i->name, input->name); */
	strcpy(i->name, "unset");

	if (input->type == CX23885_VMUX_TELEVISION ||
	    input->type == CX23885_VMUX_CABLE)
		i->type = V4L2_INPUT_TYPE_TUNER;
	else
		i->type  = V4L2_INPUT_TYPE_CAMERA;

	for (n = 0; n < ARRAY_SIZE(cx23885_tvnorms); n++)
		i->std |= cx23885_tvnorms[n].id;
	return 0;
}