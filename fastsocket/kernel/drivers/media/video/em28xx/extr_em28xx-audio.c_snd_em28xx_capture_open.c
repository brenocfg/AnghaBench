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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct em28xx* private_data; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {scalar_t__ users; struct snd_pcm_substream* capture_pcm_substream; } ;
struct em28xx {int alt; int /*<<< orphan*/  lock; TYPE_1__ adev; int /*<<< orphan*/  udev; scalar_t__ mute; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int em28xx_audio_analog_set (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_err (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_em28xx_hw_capture ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct em28xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_em28xx_capture_open(struct snd_pcm_substream *substream)
{
	struct em28xx *dev = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int ret = 0;

	dprintk("opening device and trying to acquire exclusive lock\n");

	if (!dev) {
		em28xx_err("BUG: em28xx can't find device struct."
				" Can't proceed with open\n");
		return -ENODEV;
	}

	/* Sets volume, mute, etc */

	dev->mute = 0;
	mutex_lock(&dev->lock);
	ret = em28xx_audio_analog_set(dev);
	if (ret < 0)
		goto err;

	runtime->hw = snd_em28xx_hw_capture;
	if (dev->alt == 0 && dev->adev.users == 0) {
		int errCode;
		dev->alt = 7;
		dprintk("changing alternate number to 7\n");
		errCode = usb_set_interface(dev->udev, 0, 7);
	}

	dev->adev.users++;
	mutex_unlock(&dev->lock);

	snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);
	dev->adev.capture_pcm_substream = substream;
	runtime->private_data = dev;

	return 0;
err:
	mutex_unlock(&dev->lock);

	em28xx_err("Error while configuring em28xx mixer\n");
	return ret;
}