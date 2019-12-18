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
struct v4l2_frequency {scalar_t__ frequency; } ;
struct maestro {int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FREQ2BITS (scalar_t__) ; 
 scalar_t__ FREQ_HI ; 
 scalar_t__ FREQ_LO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_bits_set (struct maestro*,int /*<<< orphan*/ ) ; 
 struct maestro* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
					struct v4l2_frequency *f)
{
	struct maestro *dev = video_drvdata(file);

	if (f->frequency < FREQ_LO || f->frequency > FREQ_HI)
		return -EINVAL;
	mutex_lock(&dev->lock);
	radio_bits_set(dev, FREQ2BITS(f->frequency));
	mutex_unlock(&dev->lock);
	return 0;
}