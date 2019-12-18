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
struct phaser_data {float* fbout; float fb; int skipcount; double gain; int lfoskip; double depth; int stages; float** old; float drywet; scalar_t__ phase; } ;
struct dspfilter_output {float* samples; unsigned int frames; } ;
struct dspfilter_input {float* samples; unsigned int frames; } ;

/* Variables and functions */
 double cos (scalar_t__) ; 
 int exp (int) ; 
 int phaserlfoshape ; 
 int phaserlfoskipsamples ; 

__attribute__((used)) static void phaser_process(void *data, struct dspfilter_output *output,
      const struct dspfilter_input *input)
{
   unsigned i, c;
   int s;
   float m[2], tmp[2];
   struct phaser_data *ph = (struct phaser_data*)data;
   float *out             = output->samples;

   output->samples        = input->samples;
   output->frames         = input->frames;

   for (i = 0; i < input->frames; i++, out += 2)
   {
      float in[2] = { out[0], out[1] };

      for (c = 0; c < 2; c++)
         m[c] = in[c] + ph->fbout[c] * ph->fb * 0.01f;

      if ((ph->skipcount++ % phaserlfoskipsamples) == 0)
      {
         ph->gain = 0.5 * (1.0 + cos(ph->skipcount * ph->lfoskip + ph->phase));
         ph->gain = (exp(ph->gain * phaserlfoshape) - 1.0) / (exp(phaserlfoshape) - 1);
         ph->gain = 1.0 - ph->gain * ph->depth;
      }

      for (s = 0; s < ph->stages; s++)
      {
         for (c = 0; c < 2; c++)
         {
            tmp[c] = ph->old[c][s];
            ph->old[c][s] = ph->gain * tmp[c] + m[c];
            m[c] = tmp[c] - ph->gain * ph->old[c][s];
         }
      }

      for (c = 0; c < 2; c++)
      {
         ph->fbout[c] = m[c];
         out[c] = m[c] * ph->drywet + in[c] * (1.0f - ph->drywet);
      }
   }
}