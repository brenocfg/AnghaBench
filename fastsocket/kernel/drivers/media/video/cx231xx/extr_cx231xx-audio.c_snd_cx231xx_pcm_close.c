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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {scalar_t__ users; int shutdown; } ;
struct cx231xx {int mute; int /*<<< orphan*/  wq_trigger; int /*<<< orphan*/  stream_started; TYPE_1__ adev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  Audio ; 
 int /*<<< orphan*/  INDEX_AUDIO ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cx231xx_capture_start (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_errdev (char*) ; 
 int cx231xx_set_alt_setting (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct cx231xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cx231xx_pcm_close(struct snd_pcm_substream *substream)
{
	int ret;
	struct cx231xx *dev = snd_pcm_substream_chip(substream);

	dprintk("closing device\n");

	/* inform hardware to stop streaming */
	mutex_lock(&dev->lock);
	ret = cx231xx_capture_start(dev, 0, Audio);

	/* set alternate setting for audio interface */
	/* 1 - 48000 samples per sec */
	ret = cx231xx_set_alt_setting(dev, INDEX_AUDIO, 0);
	if (ret < 0) {
		cx231xx_errdev("failed to set alternate setting !\n");

		mutex_unlock(&dev->lock);
		return ret;
	}

	dev->mute = 1;
	dev->adev.users--;
	mutex_unlock(&dev->lock);

	if (dev->adev.users == 0 && dev->adev.shutdown == 1) {
		dprintk("audio users: %d\n", dev->adev.users);
		dprintk("disabling audio stream!\n");
		dev->adev.shutdown = 0;
		dprintk("released lock\n");
		if (atomic_read(&dev->stream_started) > 0) {
			atomic_set(&dev->stream_started, 0);
			schedule_work(&dev->wq_trigger);
		}
	}
	return 0;
}