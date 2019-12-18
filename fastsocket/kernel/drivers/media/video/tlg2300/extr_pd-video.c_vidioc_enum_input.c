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
struct v4l2_input {size_t index; scalar_t__ status; int /*<<< orphan*/  std; scalar_t__ tuner; scalar_t__ audioset; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct front_face {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t POSEIDON_INPUTS ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  logs (struct front_face*) ; 
 TYPE_1__* pd_inputs ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *fh, struct v4l2_input *in)
{
	struct front_face *front = fh;

	if (in->index < 0 || in->index >= POSEIDON_INPUTS)
		return -EINVAL;
	strcpy(in->name, pd_inputs[in->index].name);
	in->type  = V4L2_INPUT_TYPE_TUNER;

	/*
	 * the audio input index mixed with this video input,
	 * Poseidon only have one audio/video, set to "0"
	 */
	in->audioset	= 0;
	in->tuner	= 0;
	in->std		= V4L2_STD_ALL;
	in->status	= 0;
	logs(front);
	return 0;
}