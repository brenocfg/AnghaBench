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
struct tremolo {int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct dspfilter_output {float* samples; unsigned int frames; } ;
struct dspfilter_input {float* samples; unsigned int frames; } ;

/* Variables and functions */
 float tremolocore_core (int /*<<< orphan*/ *,float) ; 

__attribute__((used)) static void tremolo_process(void *data, struct dspfilter_output *output,
      const struct dspfilter_input *input)
{
   unsigned i;
   float *out;
   struct tremolo *tre = (struct tremolo*)data;

   output->samples         = input->samples;
   output->frames          = input->frames;
   out                     = output->samples;

   for (i = 0; i < input->frames; i++, out += 2)
   {
      float in[2] = { out[0], out[1] };

      out[0] = tremolocore_core(&tre->left, in[0]);
      out[1] = tremolocore_core(&tre->right, in[1]);
   }
}