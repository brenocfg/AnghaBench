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
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {unsigned int active_output; TYPE_2__* card; } ;
struct file {int dummy; } ;
struct TYPE_4__ {unsigned int nof_outputs; TYPE_1__* video_outputs; } ;
struct TYPE_3__ {int /*<<< orphan*/  video_output; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  IVTV_HW_SAA7127 ; 
 int /*<<< orphan*/  SAA7127_INPUT_TYPE_NORMAL ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int ivtv_s_output(struct file *file, void *fh, unsigned int outp)
{
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;

	if (outp >= itv->card->nof_outputs)
		return -EINVAL;

	if (outp == itv->active_output) {
		IVTV_DEBUG_INFO("Output unchanged\n");
		return 0;
	}
	IVTV_DEBUG_INFO("Changing output from %d to %d\n",
		   itv->active_output, outp);

	itv->active_output = outp;
	ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_routing,
			SAA7127_INPUT_TYPE_NORMAL,
			itv->card->video_outputs[outp].video_output, 0);

	return 0;
}