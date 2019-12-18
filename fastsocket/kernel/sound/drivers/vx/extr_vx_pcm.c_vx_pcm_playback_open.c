#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vx_pipe {int /*<<< orphan*/  start_tq; struct snd_pcm_substream* substream; int /*<<< orphan*/  references; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct vx_core {int chip_status; unsigned int audio_outs; TYPE_2__ ibl; struct vx_pipe** playback_pipes; } ;
struct snd_pcm_substream {TYPE_1__* pcm; struct snd_pcm_runtime* runtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  period_bytes_min; } ;
struct snd_pcm_runtime {struct vx_pipe* private_data; TYPE_3__ hw; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int VX_STAT_IS_STALE ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vx_core* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int vx_alloc_pipe (struct vx_core*,int /*<<< orphan*/ ,unsigned int,int,struct vx_pipe**) ; 
 int /*<<< orphan*/  vx_pcm_delayed_start ; 
 TYPE_3__ vx_pcm_playback_hw ; 

__attribute__((used)) static int vx_pcm_playback_open(struct snd_pcm_substream *subs)
{
	struct snd_pcm_runtime *runtime = subs->runtime;
	struct vx_core *chip = snd_pcm_substream_chip(subs);
	struct vx_pipe *pipe = NULL;
	unsigned int audio;
	int err;

	if (chip->chip_status & VX_STAT_IS_STALE)
		return -EBUSY;

	audio = subs->pcm->device * 2;
	if (snd_BUG_ON(audio >= chip->audio_outs))
		return -EINVAL;
	
	/* playback pipe may have been already allocated for monitoring */
	pipe = chip->playback_pipes[audio];
	if (! pipe) {
		/* not allocated yet */
		err = vx_alloc_pipe(chip, 0, audio, 2, &pipe); /* stereo playback */
		if (err < 0)
			return err;
		chip->playback_pipes[audio] = pipe;
	}
	/* open for playback */
	pipe->references++;

	pipe->substream = subs;
	tasklet_init(&pipe->start_tq, vx_pcm_delayed_start, (unsigned long)subs);
	chip->playback_pipes[audio] = pipe;

	runtime->hw = vx_pcm_playback_hw;
	runtime->hw.period_bytes_min = chip->ibl.size;
	runtime->private_data = pipe;

	/* align to 4 bytes (otherwise will be problematic when 24bit is used) */ 
	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 4);
	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 4);

	return 0;
}