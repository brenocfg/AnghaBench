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
struct pcxhr_pipe {int dummy; } ;
struct snd_pcxhr {int nb_streams_play; int nb_streams_capt; TYPE_2__* capture_stream; struct pcxhr_pipe* capture_pipe; TYPE_1__* playback_stream; struct pcxhr_pipe playback_pipe; } ;
struct pcxhr_mgr {int num_cards; struct snd_pcxhr** chip; } ;
struct TYPE_4__ {struct pcxhr_pipe* pipe; } ;
struct TYPE_3__ {struct pcxhr_pipe* pipe; } ;

/* Variables and functions */
 int pcxhr_dsp_allocate_pipe (struct pcxhr_mgr*,struct pcxhr_pipe*,int,int) ; 

__attribute__((used)) static int pcxhr_config_pipes(struct pcxhr_mgr *mgr)
{
	int err, i, j;
	struct snd_pcxhr *chip;
	struct pcxhr_pipe *pipe;

	/* allocate the pipes on the dsp */
	for (i = 0; i < mgr->num_cards; i++) {
		chip = mgr->chip[i];
		if (chip->nb_streams_play) {
			pipe = &chip->playback_pipe;
			err = pcxhr_dsp_allocate_pipe( mgr, pipe, 0, i*2);
			if (err)
				return err;
			for(j = 0; j < chip->nb_streams_play; j++)
				chip->playback_stream[j].pipe = pipe;
		}
		for (j = 0; j < chip->nb_streams_capt; j++) {
			pipe = &chip->capture_pipe[j];
			err = pcxhr_dsp_allocate_pipe(mgr, pipe, 1, i*2 + j);
			if (err)
				return err;
			chip->capture_stream[j].pipe = pipe;
		}
	}
	return 0;
}