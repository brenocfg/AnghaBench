#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  double spx_word16_t ;
typedef  size_t spx_uint32_t ;
typedef  int spx_int32_t ;
struct TYPE_3__ {int filt_len; int* last_sample; size_t* samp_frac_num; double* sinc_table; int out_stride; int int_advance; int frac_advance; size_t den_rate; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 double PSHR32 (double,int) ; 
 double inner_product_double (double const*,double const*,int const) ; 

__attribute__((used)) static int resampler_basic_direct_double(SpeexResamplerState *st, spx_uint32_t channel_index, const spx_word16_t *in, spx_uint32_t *in_len, spx_word16_t *out, spx_uint32_t *out_len)
{
   const int N = st->filt_len;
   int out_sample = 0;
   int last_sample = st->last_sample[channel_index];
   spx_uint32_t samp_frac_num = st->samp_frac_num[channel_index];
   const spx_word16_t *sinc_table = st->sinc_table;
   const int out_stride = st->out_stride;
   const int int_advance = st->int_advance;
   const int frac_advance = st->frac_advance;
   const spx_uint32_t den_rate = st->den_rate;
   double sum;
   int j;

   while (!(last_sample >= (spx_int32_t)*in_len || out_sample >= (spx_int32_t)*out_len))
   {
      const spx_word16_t *sinc = & sinc_table[samp_frac_num*N];
      const spx_word16_t *iptr = & in[last_sample];

#ifndef OVERRIDE_INNER_PRODUCT_DOUBLE
      double accum[4] = {0,0,0,0};

      for(j=0;j<N;j+=4) {
        accum[0] += sinc[j]*iptr[j];
        accum[1] += sinc[j+1]*iptr[j+1];
        accum[2] += sinc[j+2]*iptr[j+2];
        accum[3] += sinc[j+3]*iptr[j+3];
      }
      sum = accum[0] + accum[1] + accum[2] + accum[3];
#else
      sum = inner_product_double(sinc, iptr, N);
#endif

      out[out_stride * out_sample++] = PSHR32(sum, 15);
      last_sample += int_advance;
      samp_frac_num += frac_advance;
      if (samp_frac_num >= den_rate)
      {
         samp_frac_num -= den_rate;
         last_sample++;
      }
   }

   st->last_sample[channel_index] = last_sample;
   st->samp_frac_num[channel_index] = samp_frac_num;
   return out_sample;
}