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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct cx23885_dev {scalar_t__ tuner_type; int /*<<< orphan*/  lock; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  call_all (struct cx23885_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cx23885_set_freq(struct cx23885_dev *dev, struct v4l2_frequency *f)
{
	if (unlikely(UNSET == dev->tuner_type))
		return -EINVAL;
	if (unlikely(f->tuner != 0))
		return -EINVAL;

	mutex_lock(&dev->lock);
	dev->freq = f->frequency;

	call_all(dev, tuner, s_frequency, f);

	/* When changing channels it is required to reset TVAUDIO */
	msleep(10);

	mutex_unlock(&dev->lock);

	return 0;
}