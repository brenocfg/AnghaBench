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
struct v4l2_input {size_t index; int std; scalar_t__ tuner; scalar_t__ audioset; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {TYPE_2__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_4__ {size_t num_inputs; int flags; int sensor_flags; TYPE_1__* inputs; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int GO7007_BOARD_HAS_TUNER ; 
 int GO7007_SENSOR_TV ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *inp)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	if (inp->index >= go->board_info->num_inputs)
		return -EINVAL;

	strncpy(inp->name, go->board_info->inputs[inp->index].name,
			sizeof(inp->name));

	/* If this board has a tuner, it will be the last input */
	if ((go->board_info->flags & GO7007_BOARD_HAS_TUNER) &&
			inp->index == go->board_info->num_inputs - 1)
		inp->type = V4L2_INPUT_TYPE_TUNER;
	else
		inp->type = V4L2_INPUT_TYPE_CAMERA;

	inp->audioset = 0;
	inp->tuner = 0;
	if (go->board_info->sensor_flags & GO7007_SENSOR_TV)
		inp->std = V4L2_STD_NTSC | V4L2_STD_PAL |
						V4L2_STD_SECAM;
	else
		inp->std = 0;

	return 0;
}