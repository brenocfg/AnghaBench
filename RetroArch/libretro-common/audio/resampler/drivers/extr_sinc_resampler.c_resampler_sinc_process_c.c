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
typedef  unsigned int uint32_t ;
struct resampler_data {unsigned int ratio; float* data_in; float* data_out; size_t input_frames; size_t output_frames; } ;
struct TYPE_2__ {int phase_bits; int subphase_bits; unsigned int time; size_t ptr; size_t taps; float* buffer_l; float* buffer_r; scalar_t__ window_type; float* phase_table; int subphase_mask; float subphase_mod; } ;
typedef  TYPE_1__ rarch_sinc_resampler_t ;

/* Variables and functions */
 scalar_t__ SINC_WINDOW_KAISER ; 

__attribute__((used)) static void resampler_sinc_process_c(void *re_, struct resampler_data *data)
{
   rarch_sinc_resampler_t *resamp = (rarch_sinc_resampler_t*)re_;
   unsigned phases                = 1 << (resamp->phase_bits + resamp->subphase_bits);

   uint32_t ratio                 = phases / data->ratio;
   const float *input             = data->data_in;
   float *output                  = data->data_out;
   size_t frames                  = data->input_frames;
   size_t out_frames              = 0;

   while (frames)
   {
      while (frames && resamp->time >= phases)
      {
         /* Push in reverse to make filter more obvious. */
         if (!resamp->ptr)
            resamp->ptr = resamp->taps;
         resamp->ptr--;

         resamp->buffer_l[resamp->ptr + resamp->taps]    =
            resamp->buffer_l[resamp->ptr]                = *input++;

         resamp->buffer_r[resamp->ptr + resamp->taps]    =
            resamp->buffer_r[resamp->ptr]                = *input++;

         resamp->time                                   -= phases;
         frames--;
      }

      while (resamp->time < phases)
      {
         unsigned i;
         float delta              = 0.0f;
         float sum_l              = 0.0f;
         float sum_r              = 0.0f;
         float *phase_table       = NULL;
         float *delta_table       = NULL;
         const float *buffer_l    = resamp->buffer_l + resamp->ptr;
         const float *buffer_r    = resamp->buffer_r + resamp->ptr;
         unsigned taps            = resamp->taps;
         unsigned phase           = resamp->time >> resamp->subphase_bits;

         if (resamp->window_type == SINC_WINDOW_KAISER)
         {
            phase_table           = resamp->phase_table + phase * taps * 2;
            delta_table           = phase_table + taps;
            delta                 = (float)
               (resamp->time & resamp->subphase_mask) * resamp->subphase_mod;
         }
         else
         {
            phase_table           = resamp->phase_table + phase * taps;
         }

         for (i = 0; i < taps; i++)
         {
            float sinc_val        = phase_table[i];

            if (resamp->window_type == SINC_WINDOW_KAISER)
               sinc_val           = sinc_val + delta_table[i] * delta;

            sum_l                += buffer_l[i] * sinc_val;
            sum_r                += buffer_r[i] * sinc_val;
         }

         output[0]                = sum_l;
         output[1]                = sum_r;

         output                  += 2;
         out_frames++;
         resamp->time            += ratio;
      }

   }

   data->output_frames = out_frames;
}