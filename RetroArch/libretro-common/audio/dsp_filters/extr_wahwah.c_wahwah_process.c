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
struct TYPE_4__ {float xn1; float xn2; float yn1; float yn2; } ;
struct TYPE_3__ {float xn1; float xn2; float yn1; float yn2; } ;
struct wahwah_data {int skipcount; int lfoskip; float phase; float depth; double freqofs; double res; double b0; double b1; double b2; double a0; double a1; double a2; TYPE_2__ r; TYPE_1__ l; } ;
struct dspfilter_output {float* samples; unsigned int frames; } ;
struct dspfilter_input {float* samples; unsigned int frames; } ;

/* Variables and functions */
 float M_PI ; 
 int WAHWAH_LFO_SKIP_SAMPLES ; 
 double cos (float) ; 
 float exp (float) ; 
 float sin (float) ; 

__attribute__((used)) static void wahwah_process(void *data, struct dspfilter_output *output,
      const struct dspfilter_input *input)
{
   unsigned i;
   struct wahwah_data *wah = (struct wahwah_data*)data;
   float *out              = output->samples;

   output->samples         = input->samples;
   output->frames          = input->frames;

   for (i = 0; i < input->frames; i++, out += 2)
   {
      float out_l, out_r;
      float in[2] = { out[0], out[1] };

      if ((wah->skipcount++ % WAHWAH_LFO_SKIP_SAMPLES) == 0)
      {
         float omega, sn, cs, alpha;
         float frequency = (1.0 + cos(wah->skipcount * wah->lfoskip + wah->phase)) / 2.0;

         frequency = frequency * wah->depth * (1.0 - wah->freqofs) + wah->freqofs;
         frequency = exp((frequency - 1.0) * 6.0);

         omega     = M_PI * frequency;
         sn        = sin(omega);
         cs        = cos(omega);
         alpha     = sn / (2.0 * wah->res);

         wah->b0   = (1.0 - cs) / 2.0;
         wah->b1   = 1.0 - cs;
         wah->b2   = (1.0 - cs) / 2.0;
         wah->a0   = 1.0 + alpha;
         wah->a1   = -2.0 * cs;
         wah->a2   = 1.0 - alpha;
      }

      out_l      = (wah->b0 * in[0] + wah->b1 * wah->l.xn1 + wah->b2 * wah->l.xn2 - wah->a1 * wah->l.yn1 - wah->a2 * wah->l.yn2) / wah->a0;
      out_r      = (wah->b0 * in[1] + wah->b1 * wah->r.xn1 + wah->b2 * wah->r.xn2 - wah->a1 * wah->r.yn1 - wah->a2 * wah->r.yn2) / wah->a0;

      wah->l.xn2 = wah->l.xn1;
      wah->l.xn1 = in[0];
      wah->l.yn2 = wah->l.yn1;
      wah->l.yn1 = out_l;

      wah->r.xn2 = wah->r.xn1;
      wah->r.xn1 = in[1];
      wah->r.yn2 = wah->r.yn1;
      wah->r.yn1 = out_r;

      out[0]     = out_l;
      out[1]     = out_r;
   }
}