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
struct v4l2_frequency {int /*<<< orphan*/  frequency; } ;
struct cx25821_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25821_call_all (struct cx25821_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 

int cx25821_set_freq(struct cx25821_dev *dev, struct v4l2_frequency *f)
{
	mutex_lock(&dev->lock);
	dev->freq = f->frequency;

	cx25821_call_all(dev, tuner, s_frequency, f);

	/* When changing channels it is required to reset TVAUDIO */
	msleep(10);

	mutex_unlock(&dev->lock);

	return 0;
}