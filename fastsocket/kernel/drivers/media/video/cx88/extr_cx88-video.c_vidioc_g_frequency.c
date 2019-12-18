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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct TYPE_4__ {scalar_t__ tuner_type; } ;
struct cx88_core {int /*<<< orphan*/  freq; TYPE_2__ board; } ;
struct cx8800_fh {scalar_t__ radio; TYPE_1__* dev; } ;
struct TYPE_3__ {struct cx88_core* core; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vidioc_g_frequency (struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct cx8800_fh  *fh   = priv;
	struct cx88_core  *core = fh->dev->core;

	if (unlikely(UNSET == core->board.tuner_type))
		return -EINVAL;

	/* f->type = fh->radio ? V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV; */
	f->type = fh->radio ? V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
	f->frequency = core->freq;

	call_all(core, tuner, g_frequency, f);

	return 0;
}