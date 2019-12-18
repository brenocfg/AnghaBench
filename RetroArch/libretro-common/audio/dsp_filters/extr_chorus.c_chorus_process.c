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
struct dspfilter_output {float* samples; unsigned int frames; } ;
struct dspfilter_input {float* samples; unsigned int frames; } ;
struct chorus_data {float delay; float depth; double lfo_ptr; double lfo_period; float input_rate; float** old; size_t old_ptr; float mix_dry; float mix_wet; } ;

/* Variables and functions */
 size_t CHORUS_DELAY_MASK ; 
 int CHORUS_MAX_DELAY ; 
 double M_PI ; 
 float sin (double) ; 

__attribute__((used)) static void chorus_process(void *data, struct dspfilter_output *output,
      const struct dspfilter_input *input)
{
   unsigned i;
   float *out             = NULL;
   struct chorus_data *ch = (struct chorus_data*)data;

   output->samples        = input->samples;
   output->frames         = input->frames;
   out                    = output->samples;

   for (i = 0; i < input->frames; i++, out += 2)
   {
      unsigned delay_int;
      float delay_frac, l_a, l_b, r_a, r_b;
      float chorus_l, chorus_r;
      float in[2] = { out[0], out[1] };
      float delay = ch->delay + ch->depth * sin((2.0 * M_PI * ch->lfo_ptr++) / ch->lfo_period);

      delay *= ch->input_rate;
      if (ch->lfo_ptr >= ch->lfo_period)
         ch->lfo_ptr = 0;

      delay_int = (unsigned)delay;

      if (delay_int >= CHORUS_MAX_DELAY - 1)
         delay_int = CHORUS_MAX_DELAY - 2;

      delay_frac = delay - delay_int;

      ch->old[0][ch->old_ptr] = in[0];
      ch->old[1][ch->old_ptr] = in[1];

      l_a         = ch->old[0][(ch->old_ptr - delay_int - 0) & CHORUS_DELAY_MASK];
      l_b         = ch->old[0][(ch->old_ptr - delay_int - 1) & CHORUS_DELAY_MASK];
      r_a         = ch->old[1][(ch->old_ptr - delay_int - 0) & CHORUS_DELAY_MASK];
      r_b         = ch->old[1][(ch->old_ptr - delay_int - 1) & CHORUS_DELAY_MASK];

      /* Lerp introduces aliasing of the chorus component,
       * but doing full polyphase here is probably overkill. */
      chorus_l    = l_a * (1.0f - delay_frac) + l_b * delay_frac;
      chorus_r    = r_a * (1.0f - delay_frac) + r_b * delay_frac;

      out[0]      = ch->mix_dry * in[0] + ch->mix_wet * chorus_l;
      out[1]      = ch->mix_dry * in[1] + ch->mix_wet * chorus_r;

      ch->old_ptr = (ch->old_ptr + 1) & CHORUS_DELAY_MASK;
   }
}