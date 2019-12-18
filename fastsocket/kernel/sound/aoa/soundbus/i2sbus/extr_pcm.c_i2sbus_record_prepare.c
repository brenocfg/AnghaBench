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
struct i2sbus_dev {TYPE_1__ in; } ;

/* Variables and functions */
 int EINVAL ; 
 int i2sbus_pcm_prepare (struct i2sbus_dev*,int) ; 
 struct i2sbus_dev* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int i2sbus_record_prepare(struct snd_pcm_substream *substream)
{
	struct i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	if (!i2sdev)
		return -EINVAL;
	if (i2sdev->in.substream != substream)
		return -EINVAL;
	return i2sbus_pcm_prepare(i2sdev, 1);
}