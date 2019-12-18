#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct retro_dsp_data {int /*<<< orphan*/  output_frames; int /*<<< orphan*/  output; int /*<<< orphan*/  input_frames; int /*<<< orphan*/  input; } ;
struct dspfilter_output {int /*<<< orphan*/  frames; int /*<<< orphan*/  samples; int /*<<< orphan*/  member_0; } ;
struct dspfilter_input {int /*<<< orphan*/  frames; int /*<<< orphan*/  samples; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {unsigned int num_instances; TYPE_2__* instances; } ;
typedef  TYPE_3__ retro_dsp_filter_t ;
struct TYPE_6__ {int /*<<< orphan*/  impl_data; TYPE_1__* impl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* process ) (int /*<<< orphan*/ ,struct dspfilter_output*,struct dspfilter_input*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dspfilter_output*,struct dspfilter_input*) ; 

void retro_dsp_filter_process(retro_dsp_filter_t *dsp,
      struct retro_dsp_data *data)
{
   unsigned i;
   struct dspfilter_output output = {0};
   struct dspfilter_input input   = {0};

   output.samples = data->input;
   output.frames  = data->input_frames;

   for (i = 0; i < dsp->num_instances; i++)
   {
      input.samples = output.samples;
      input.frames  = output.frames;
      dsp->instances[i].impl->process(
            dsp->instances[i].impl_data, &output, &input);
   }

   data->output        = output.samples;
   data->output_frames = output.frames;
}