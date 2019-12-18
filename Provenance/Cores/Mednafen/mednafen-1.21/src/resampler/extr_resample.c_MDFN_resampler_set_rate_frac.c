#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ spx_uint32_t ;
struct TYPE_4__ {scalar_t__ in_rate; scalar_t__ out_rate; scalar_t__ num_rate; scalar_t__ den_rate; scalar_t__ nb_channels; scalar_t__* samp_frac_num; scalar_t__ initialised; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 scalar_t__ IMIN (scalar_t__,scalar_t__) ; 
 int RESAMPLER_ERR_SUCCESS ; 
 int /*<<< orphan*/  update_filter (TYPE_1__*) ; 

int speex_resampler_set_rate_frac(SpeexResamplerState *st, spx_uint32_t ratio_num, spx_uint32_t ratio_den, spx_uint32_t in_rate, spx_uint32_t out_rate)
{
   spx_uint32_t fact;
   spx_uint32_t old_den;
   spx_uint32_t i;
   if (st->in_rate == in_rate && st->out_rate == out_rate && st->num_rate == ratio_num && st->den_rate == ratio_den)
      return RESAMPLER_ERR_SUCCESS;
   
   old_den = st->den_rate;
   st->in_rate = in_rate;
   st->out_rate = out_rate;
   st->num_rate = ratio_num;
   st->den_rate = ratio_den;
   /* FIXME: This is terribly inefficient, but who cares (at least for now)? */
   for (fact=2;fact<=IMIN(st->num_rate, st->den_rate);fact++)
   {
      while ((st->num_rate % fact == 0) && (st->den_rate % fact == 0))
      {
         st->num_rate /= fact;
         st->den_rate /= fact;
      }
   }
      
   if (old_den > 0)
   {
      for (i=0;i<st->nb_channels;i++)
      {
         st->samp_frac_num[i]=st->samp_frac_num[i]*st->den_rate/old_den;
         /* Safety net */
         if (st->samp_frac_num[i] >= st->den_rate)
            st->samp_frac_num[i] = st->den_rate-1;
      }
   }
   
   if (st->initialised)
      update_filter(st);
   return RESAMPLER_ERR_SUCCESS;
}