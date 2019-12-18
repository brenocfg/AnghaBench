#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_audio {scalar_t__ index; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {scalar_t__ nof_audio_inputs; scalar_t__ audio_input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ivtv_audio_set_io (struct ivtv*) ; 

__attribute__((used)) static int ivtv_s_audio(struct file *file, void *fh, struct v4l2_audio *vout)
{
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;

	if (vout->index >= itv->nof_audio_inputs)
		return -EINVAL;

	itv->audio_input = vout->index;
	ivtv_audio_set_io(itv);

	return 0;
}