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
struct v4l2_frequency {scalar_t__ tuner; int frequency; } ;
struct tea5764_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FREQ_MAX ; 
 int FREQ_MIN ; 
 int FREQ_MUL ; 
 int /*<<< orphan*/  tea5764_power_down (struct tea5764_device*) ; 
 int /*<<< orphan*/  tea5764_power_up (struct tea5764_device*) ; 
 int /*<<< orphan*/  tea5764_tune (struct tea5764_device*,int) ; 
 struct tea5764_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct tea5764_device *radio = video_drvdata(file);

	if (f->tuner != 0)
		return -EINVAL;
	if (f->frequency == 0) {
		/* We special case this as a power down control. */
		tea5764_power_down(radio);
	}
	if (f->frequency < (FREQ_MIN * FREQ_MUL))
		return -EINVAL;
	if (f->frequency > (FREQ_MAX * FREQ_MUL))
		return -EINVAL;
	tea5764_power_up(radio);
	tea5764_tune(radio, (f->frequency * 125) / 2);
	return 0;
}