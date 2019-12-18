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
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;
struct i2sbus_dev {TYPE_1__ out; } ;

/* Variables and functions */
 int EINVAL ; 
 int i2sbus_pcm_trigger (struct i2sbus_dev*,int /*<<< orphan*/ ,int) ; 
 struct i2sbus_dev* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int i2sbus_playback_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	if (!i2sdev)
		return -EINVAL;
	if (i2sdev->out.substream != substream)
		return -EINVAL;
	return i2sbus_pcm_trigger(i2sdev, 0, cmd);
}