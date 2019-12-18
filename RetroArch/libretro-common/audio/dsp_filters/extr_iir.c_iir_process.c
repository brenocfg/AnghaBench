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
struct iir_data {float b0; float b1; float b2; float a0; float a1; float a2; TYPE_2__ r; TYPE_1__ l; } ;
struct dspfilter_output {float* samples; unsigned int frames; } ;
struct dspfilter_input {float* samples; unsigned int frames; } ;

/* Variables and functions */

__attribute__((used)) static void iir_process(void *data, struct dspfilter_output *output,
      const struct dspfilter_input *input)
{
   unsigned i;
   struct iir_data *iir = (struct iir_data*)data;
   float *out           = output->samples;

   float b0             = iir->b0;
   float b1             = iir->b1;
   float b2             = iir->b2;
   float a0             = iir->a0;
   float a1             = iir->a1;
   float a2             = iir->a2;

   float xn1_l          = iir->l.xn1;
   float xn2_l          = iir->l.xn2;
   float yn1_l          = iir->l.yn1;
   float yn2_l          = iir->l.yn2;

   float xn1_r          = iir->r.xn1;
   float xn2_r          = iir->r.xn2;
   float yn1_r          = iir->r.yn1;
   float yn2_r          = iir->r.yn2;

   output->samples      = input->samples;
   output->frames       = input->frames;

   for (i = 0; i < input->frames; i++, out += 2)
   {
      float in_l = out[0];
      float in_r = out[1];

      float l    = (b0 * in_l + b1 * xn1_l + b2 * xn2_l - a1 * yn1_l - a2 * yn2_l) / a0;
      float r    = (b0 * in_r + b1 * xn1_r + b2 * xn2_r - a1 * yn1_r - a2 * yn2_r) / a0;

      xn2_l      = xn1_l;
      xn1_l      = in_l;
      yn2_l      = yn1_l;
      yn1_l      = l;

      xn2_r      = xn1_r;
      xn1_r      = in_r;
      yn2_r      = yn1_r;
      yn1_r      = r;

      out[0]     = l;
      out[1]     = r;
   }

   iir->l.xn1 = xn1_l;
   iir->l.xn2 = xn2_l;
   iir->l.yn1 = yn1_l;
   iir->l.yn2 = yn2_l;

   iir->r.xn1 = xn1_r;
   iir->r.xn2 = xn2_r;
   iir->r.yn1 = yn1_r;
   iir->r.yn2 = yn2_r;
}