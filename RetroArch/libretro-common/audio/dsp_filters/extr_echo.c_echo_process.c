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
struct echo_data {unsigned int num_channels; float amp; TYPE_1__* channels; } ;
struct dspfilter_output {float* samples; unsigned int frames; } ;
struct dspfilter_input {float* samples; unsigned int frames; } ;
struct TYPE_2__ {float* buffer; int ptr; float feedback; int frames; } ;

/* Variables and functions */

__attribute__((used)) static void echo_process(void *data, struct dspfilter_output *output,
      const struct dspfilter_input *input)
{
   unsigned i, c;
   float *out             = NULL;
   struct echo_data *echo = (struct echo_data*)data;

   output->samples        = input->samples;
   output->frames         = input->frames;

   out                    = output->samples;

   for (i = 0; i < input->frames; i++, out += 2)
   {
      float left, right;
      float echo_left  = 0.0f;
      float echo_right = 0.0f;

      for (c = 0; c < echo->num_channels; c++)
      {
         echo_left  += echo->channels[c].buffer[(echo->channels[c].ptr << 1) + 0];
         echo_right += echo->channels[c].buffer[(echo->channels[c].ptr << 1) + 1];
      }

      echo_left  *= echo->amp;
      echo_right *= echo->amp;

      left        = out[0] + echo_left;
      right       = out[1] + echo_right;

      for (c = 0; c < echo->num_channels; c++)
      {
         float feedback_left  = out[0] + echo->channels[c].feedback * echo_left;
         float feedback_right = out[1] + echo->channels[c].feedback * echo_right;

         echo->channels[c].buffer[(echo->channels[c].ptr << 1) + 0] = feedback_left;
         echo->channels[c].buffer[(echo->channels[c].ptr << 1) + 1] = feedback_right;

         echo->channels[c].ptr = (echo->channels[c].ptr + 1) % echo->channels[c].frames;
      }

      out[0] = left;
      out[1] = right;
   }
}