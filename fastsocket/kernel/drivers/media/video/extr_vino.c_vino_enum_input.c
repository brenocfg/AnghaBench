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
struct vino_channel_settings {int dummy; } ;
struct v4l2_input {int /*<<< orphan*/  status; int /*<<< orphan*/  name; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  std; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int VINO_INPUT_COMPOSITE ; 
 int VINO_INPUT_NONE ; 
 int VINO_INPUT_SVIDEO ; 
 int /*<<< orphan*/  decoder_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_input_status ; 
 int /*<<< orphan*/  memset (struct v4l2_input*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 TYPE_1__* vino_inputs ; 
 int vino_int_enum_input (struct vino_channel_settings*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vino_enum_input(struct file *file, void *__fh,
			       struct v4l2_input *i)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	__u32 index = i->index;
	int input;
	dprintk("requested index = %d\n", index);

	input = vino_int_enum_input(vcs, index);
	if (input == VINO_INPUT_NONE)
		return -EINVAL;

	memset(i, 0, sizeof(struct v4l2_input));

	i->index = index;
	i->type = V4L2_INPUT_TYPE_CAMERA;
	i->std = vino_inputs[input].std;
	strcpy(i->name, vino_inputs[input].name);

	if (input == VINO_INPUT_COMPOSITE || input == VINO_INPUT_SVIDEO)
		decoder_call(video, g_input_status, &i->status);
	return 0;
}