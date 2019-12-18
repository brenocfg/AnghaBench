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
struct panning_data {float* left; float* right; } ;
struct dspfilter_output {float* samples; unsigned int frames; } ;
struct dspfilter_input {float* samples; unsigned int frames; } ;

/* Variables and functions */

__attribute__((used)) static void panning_process(void *data, struct dspfilter_output *output,
      const struct dspfilter_input *input)
{
   unsigned i;
   struct panning_data *pan = (struct panning_data*)data;
   float *out               = output->samples;

   output->samples          = input->samples;
   output->frames           = input->frames;

   for (i = 0; i < input->frames; i++, out += 2)
   {
      float left  = out[0];
      float right = out[1];
      out[0]      = left * pan->left[0]  + right * pan->left[1];
      out[1]      = left * pan->right[0] + right * pan->right[1];
   }
}