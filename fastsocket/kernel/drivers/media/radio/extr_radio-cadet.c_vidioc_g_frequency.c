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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; int /*<<< orphan*/  tuner; } ;
struct file {int dummy; } ;
struct cadet {int /*<<< orphan*/  curtuner; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  cadet_getfreq (struct cadet*) ; 
 struct cadet* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct cadet *dev = video_drvdata(file);

	f->tuner = dev->curtuner;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = cadet_getfreq(dev);
	return 0;
}