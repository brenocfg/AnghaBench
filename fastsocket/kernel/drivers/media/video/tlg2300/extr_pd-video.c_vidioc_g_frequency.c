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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  type; int /*<<< orphan*/  frequency; } ;
struct running_context {int /*<<< orphan*/  freq; } ;
struct TYPE_2__ {struct running_context context; } ;
struct poseidon {TYPE_1__ video_data; } ;
struct front_face {struct poseidon* pd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *fh,
			struct v4l2_frequency *freq)
{
	struct front_face *front = fh;
	struct poseidon *pd = front->pd;
	struct running_context *context = &pd->video_data.context;

	if (0 != freq->tuner)
		return -EINVAL;
	freq->frequency = context->freq;
	freq->type = V4L2_TUNER_ANALOG_TV;
	return 0;
}