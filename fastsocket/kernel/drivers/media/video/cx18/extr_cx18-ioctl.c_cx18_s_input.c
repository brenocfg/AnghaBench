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
struct file {int dummy; } ;
struct cx18_open_id {int /*<<< orphan*/  prio; struct cx18* cx; } ;
struct cx18 {unsigned int nof_inputs; unsigned int active_input; TYPE_2__* card; int /*<<< orphan*/  audio_input; int /*<<< orphan*/  prio; } ;
struct TYPE_4__ {TYPE_1__* video_inputs; } ;
struct TYPE_3__ {int /*<<< orphan*/  audio_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cx18_audio_set_io (struct cx18*) ; 
 int /*<<< orphan*/  cx18_mute (struct cx18*) ; 
 int /*<<< orphan*/  cx18_unmute (struct cx18*) ; 
 int /*<<< orphan*/  cx18_video_set_io (struct cx18*) ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cx18_s_input(struct file *file, void *fh, unsigned int inp)
{
	struct cx18_open_id *id = fh;
	struct cx18 *cx = id->cx;
	int ret;

	ret = v4l2_prio_check(&cx->prio, id->prio);
	if (ret)
		return ret;

	if (inp >= cx->nof_inputs)
		return -EINVAL;

	if (inp == cx->active_input) {
		CX18_DEBUG_INFO("Input unchanged\n");
		return 0;
	}

	CX18_DEBUG_INFO("Changing input from %d to %d\n",
			cx->active_input, inp);

	cx->active_input = inp;
	/* Set the audio input to whatever is appropriate for the input type. */
	cx->audio_input = cx->card->video_inputs[inp].audio_index;

	/* prevent others from messing with the streams until
	   we're finished changing inputs. */
	cx18_mute(cx);
	cx18_video_set_io(cx);
	cx18_audio_set_io(cx);
	cx18_unmute(cx);
	return 0;
}