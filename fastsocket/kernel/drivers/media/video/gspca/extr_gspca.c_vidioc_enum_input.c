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
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  name; int /*<<< orphan*/  status; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  input_flags; } ;
struct gspca_dev {TYPE_2__* sd_desc; TYPE_1__ cam; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *input)
{
	struct gspca_dev *gspca_dev = priv;

	if (input->index != 0)
		return -EINVAL;
	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->status = gspca_dev->cam.input_flags;
	strncpy(input->name, gspca_dev->sd_desc->name,
		sizeof input->name);
	return 0;
}