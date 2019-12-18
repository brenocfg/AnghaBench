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
struct v4l2_frequency {int frequency; } ;
struct maxiradio {int freq; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FREQ_HI ; 
 int FREQ_LO ; 
 int /*<<< orphan*/  dprintk (struct maxiradio*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_freq (struct maxiradio*,int) ; 
 struct maxiradio* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
			       struct v4l2_frequency *f)
{
	struct maxiradio *dev = video_drvdata(file);

	if (f->frequency < FREQ_LO || f->frequency > FREQ_HI) {
		dprintk(dev, 1, "radio freq (%d.%02d MHz) out of range (%d-%d)\n",
					f->frequency / 16000,
					f->frequency % 16000 * 100 / 16000,
					FREQ_LO / 16000, FREQ_HI / 16000);

		return -EINVAL;
	}

	mutex_lock(&dev->lock);
	dev->freq = f->frequency;
	set_freq(dev, dev->freq);
	msleep(125);
	mutex_unlock(&dev->lock);

	return 0;
}