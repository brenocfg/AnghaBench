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
struct snd_pcm_substream {size_t stream; struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  rates; int /*<<< orphan*/  formats; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; } ;
struct snd_pcm_runtime {struct azx_dev* private_data; TYPE_2__ hw; } ;
struct TYPE_3__ {int (* open ) (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ;int /*<<< orphan*/  (* close ) (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ;} ;
struct hda_pcm_stream {TYPE_1__ ops; int /*<<< orphan*/  rates; int /*<<< orphan*/  formats; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; } ;
struct azx_pcm {int /*<<< orphan*/  codec; struct azx* chip; struct hda_pcm_stream** hinfo; } ;
struct azx_dev {scalar_t__ running; struct snd_pcm_substream* substream; } ;
struct azx {int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  reg_lock; scalar_t__ align_buffer_size; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 struct azx_dev* azx_assign_device (struct azx*,struct snd_pcm_substream*) ; 
 TYPE_2__ azx_pcm_hw ; 
 int /*<<< orphan*/  azx_release_device (struct azx_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_hda_power_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_power_up_d3wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub2 (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

__attribute__((used)) static int azx_pcm_open(struct snd_pcm_substream *substream)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct hda_pcm_stream *hinfo = apcm->hinfo[substream->stream];
	struct azx *chip = apcm->chip;
	struct azx_dev *azx_dev;
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long flags;
	int err;
	int buff_step;

	mutex_lock(&chip->open_mutex);
	azx_dev = azx_assign_device(chip, substream);
	if (azx_dev == NULL) {
		mutex_unlock(&chip->open_mutex);
		return -EBUSY;
	}
	runtime->hw = azx_pcm_hw;
	runtime->hw.channels_min = hinfo->channels_min;
	runtime->hw.channels_max = hinfo->channels_max;
	runtime->hw.formats = hinfo->formats;
	runtime->hw.rates = hinfo->rates;
	snd_pcm_limit_hw_rates(runtime);
	snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);
	if (chip->align_buffer_size)
		/* constrain buffer sizes to be multiple of 128
		   bytes. This is more efficient in terms of memory
		   access but isn't required by the HDA spec and
		   prevents users from specifying exact period/buffer
		   sizes. For example for 44.1kHz, a period size set
		   to 20ms will be rounded to 19.59ms. */
		buff_step = 128;
	else
		/* Don't enforce steps on buffer sizes, still need to
		   be multiple of 4 bytes (HDA spec). Tested on Intel
		   HDA controllers, may not work on all devices where
		   option needs to be disabled */
		buff_step = 4;

	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   buff_step);
	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   buff_step);
	snd_hda_power_up_d3wait(apcm->codec);
	err = hinfo->ops.open(hinfo, apcm->codec, substream);
	if (err < 0) {
		azx_release_device(azx_dev);
		snd_hda_power_down(apcm->codec);
		mutex_unlock(&chip->open_mutex);
		return err;
	}
	snd_pcm_limit_hw_rates(runtime);
	/* sanity check */
	if (snd_BUG_ON(!runtime->hw.channels_min) ||
	    snd_BUG_ON(!runtime->hw.channels_max) ||
	    snd_BUG_ON(!runtime->hw.formats) ||
	    snd_BUG_ON(!runtime->hw.rates)) {
		azx_release_device(azx_dev);
		hinfo->ops.close(hinfo, apcm->codec, substream);
		snd_hda_power_down(apcm->codec);
		mutex_unlock(&chip->open_mutex);
		return -EINVAL;
	}
	spin_lock_irqsave(&chip->reg_lock, flags);
	azx_dev->substream = substream;
	azx_dev->running = 0;
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	runtime->private_data = azx_dev;
	snd_pcm_set_sync(substream);
	mutex_unlock(&chip->open_mutex);
	return 0;
}