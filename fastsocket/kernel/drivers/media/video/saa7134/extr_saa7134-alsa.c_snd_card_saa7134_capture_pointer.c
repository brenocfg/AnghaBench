#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_2__* private_data; } ;
struct TYPE_3__ {scalar_t__ read_count; scalar_t__ read_offset; scalar_t__ bufsize; } ;
struct saa7134_dev {TYPE_1__ dmasound; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_4__ {struct saa7134_dev* dev; } ;
typedef  TYPE_2__ snd_card_saa7134_pcm_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,scalar_t__) ; 
 scalar_t__ snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_card_saa7134_capture_pointer(struct snd_pcm_substream * substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_card_saa7134_pcm_t *pcm = runtime->private_data;
	struct saa7134_dev *dev=pcm->dev;

	if (dev->dmasound.read_count) {
		dev->dmasound.read_count  -= snd_pcm_lib_period_bytes(substream);
		dev->dmasound.read_offset += snd_pcm_lib_period_bytes(substream);
		if (dev->dmasound.read_offset == dev->dmasound.bufsize)
			dev->dmasound.read_offset = 0;
	}

	return bytes_to_frames(runtime, dev->dmasound.read_offset);
}