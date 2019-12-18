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
struct vx_pipe {int running; int /*<<< orphan*/  start_tq; int /*<<< orphan*/  is_capture; } ;
struct vx_core {int chip_status; int /*<<< orphan*/  pcm_running; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct vx_pipe* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int VX_STAT_IS_STALE ; 
 struct vx_core* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vx_pcm_playback_transfer (struct vx_core*,struct snd_pcm_substream*,struct vx_pipe*,int) ; 
 int /*<<< orphan*/  vx_stop_pipe (struct vx_core*,struct vx_pipe*) ; 
 int /*<<< orphan*/  vx_stop_stream (struct vx_core*,struct vx_pipe*) ; 
 int vx_toggle_pipe (struct vx_core*,struct vx_pipe*,int) ; 

__attribute__((used)) static int vx_pcm_trigger(struct snd_pcm_substream *subs, int cmd)
{
	struct vx_core *chip = snd_pcm_substream_chip(subs);
	struct vx_pipe *pipe = subs->runtime->private_data;
	int err;

	if (chip->chip_status & VX_STAT_IS_STALE)
		return -EBUSY;
		
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (! pipe->is_capture)
			vx_pcm_playback_transfer(chip, subs, pipe, 2);
		/* FIXME:
		 * we trigger the pipe using tasklet, so that the interrupts are
		 * issued surely after the trigger is completed.
		 */ 
		tasklet_schedule(&pipe->start_tq);
		chip->pcm_running++;
		pipe->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		vx_toggle_pipe(chip, pipe, 0);
		vx_stop_pipe(chip, pipe);
		vx_stop_stream(chip, pipe);
		chip->pcm_running--;
		pipe->running = 0;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if ((err = vx_toggle_pipe(chip, pipe, 0)) < 0)
			return err;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if ((err = vx_toggle_pipe(chip, pipe, 1)) < 0)
			return err;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}