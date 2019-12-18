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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct maestro {int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS2FREQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_bits_get (struct maestro*) ; 
 struct maestro* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
					struct v4l2_frequency *f)
{
	struct maestro *dev = video_drvdata(file);

	f->type = V4L2_TUNER_RADIO;
	mutex_lock(&dev->lock);
	f->frequency = BITS2FREQ(radio_bits_get(dev));
	mutex_unlock(&dev->lock);
	return 0;
}