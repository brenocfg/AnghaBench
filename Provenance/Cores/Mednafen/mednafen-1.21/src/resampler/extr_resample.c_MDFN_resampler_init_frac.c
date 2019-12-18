#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int spx_uint32_t ;
typedef  scalar_t__ spx_int32_t ;
struct TYPE_6__ {int initialised; int quality; float cutoff; int nb_channels; int in_stride; int out_stride; int buffer_size; int* magic_samples; int* samp_frac_num; scalar_t__* last_sample; scalar_t__ resampler_ptr; scalar_t__ mem; scalar_t__ filt_len; scalar_t__ mem_alloc_size; scalar_t__ sinc_table_length; scalar_t__ den_rate; scalar_t__ num_rate; scalar_t__ out_rate; scalar_t__ in_rate; scalar_t__ started; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 int RESAMPLER_ERR_INVALID_ARG ; 
 int RESAMPLER_ERR_SUCCESS ; 
 scalar_t__ speex_alloc (int) ; 
 int /*<<< orphan*/  speex_resampler_set_quality (TYPE_1__*,int) ; 
 int /*<<< orphan*/  speex_resampler_set_rate_frac (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  update_filter (TYPE_1__*) ; 

SpeexResamplerState *speex_resampler_init_frac(spx_uint32_t nb_channels, spx_uint32_t ratio_num, spx_uint32_t ratio_den, spx_uint32_t in_rate, spx_uint32_t out_rate, int quality, int *err)
{
   spx_uint32_t i;
   SpeexResamplerState *st;
   if (quality > 10 || quality < 0)
   {
      if (err)
         *err = RESAMPLER_ERR_INVALID_ARG;
      return NULL;
   }
   st = (SpeexResamplerState *)speex_alloc(sizeof(SpeexResamplerState));
   st->initialised = 0;
   st->started = 0;
   st->in_rate = 0;
   st->out_rate = 0;
   st->num_rate = 0;
   st->den_rate = 0;
   st->quality = -1;
   st->sinc_table_length = 0;
   st->mem_alloc_size = 0;
   st->filt_len = 0;
   st->mem = 0;
   st->resampler_ptr = 0;
         
   st->cutoff = 1.f;
   st->nb_channels = nb_channels;
   st->in_stride = 1;
   st->out_stride = 1;
   
#ifdef FIXED_POINT
   st->buffer_size = 160;
#else
   st->buffer_size = 160;
#endif
   
   /* Per channel data */
   st->last_sample = (spx_int32_t*)speex_alloc(nb_channels*sizeof(int));
   st->magic_samples = (spx_uint32_t*)speex_alloc(nb_channels*sizeof(int));
   st->samp_frac_num = (spx_uint32_t*)speex_alloc(nb_channels*sizeof(int));
   for (i=0;i<nb_channels;i++)
   {
      st->last_sample[i] = 0;
      st->magic_samples[i] = 0;
      st->samp_frac_num[i] = 0;
   }

   speex_resampler_set_quality(st, quality);
   speex_resampler_set_rate_frac(st, ratio_num, ratio_den, in_rate, out_rate);

   
   update_filter(st);
   
   st->initialised = 1;
   if (err)
      *err = RESAMPLER_ERR_SUCCESS;

   return st;
}