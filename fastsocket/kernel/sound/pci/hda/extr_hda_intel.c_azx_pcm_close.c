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
struct snd_pcm_substream {size_t stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ;} ;
struct hda_pcm_stream {TYPE_1__ ops; } ;
struct azx_pcm {int /*<<< orphan*/  codec; struct azx* chip; struct hda_pcm_stream** hinfo; } ;
struct azx_dev {scalar_t__ running; int /*<<< orphan*/ * substream; } ;
struct azx {int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_release_device (struct azx_dev*) ; 
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_power_down (int /*<<< orphan*/ ) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

__attribute__((used)) static int azx_pcm_close(struct snd_pcm_substream *substream)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct hda_pcm_stream *hinfo = apcm->hinfo[substream->stream];
	struct azx *chip = apcm->chip;
	struct azx_dev *azx_dev = get_azx_dev(substream);
	unsigned long flags;

	mutex_lock(&chip->open_mutex);
	spin_lock_irqsave(&chip->reg_lock, flags);
	azx_dev->substream = NULL;
	azx_dev->running = 0;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	azx_release_device(azx_dev);
	hinfo->ops.close(hinfo, apcm->codec, substream);
	snd_hda_power_down(apcm->codec);
	mutex_unlock(&chip->open_mutex);
	return 0;
}