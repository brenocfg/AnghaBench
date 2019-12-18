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
typedef  int /*<<< orphan*/  spx_word16_t ;
typedef  size_t spx_uint32_t ;
struct TYPE_4__ {size_t* magic_samples; size_t mem_alloc_size; int filt_len; size_t out_stride; int /*<<< orphan*/ * mem; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 int /*<<< orphan*/  speex_resampler_process_native (TYPE_1__*,size_t,size_t*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int speex_resampler_magic(SpeexResamplerState *st, spx_uint32_t channel_index, spx_word16_t **out, spx_uint32_t out_len) {
   spx_uint32_t tmp_in_len = st->magic_samples[channel_index];
   spx_word16_t *mem = st->mem + channel_index * st->mem_alloc_size;
   const int N = st->filt_len;
   
   speex_resampler_process_native(st, channel_index, &tmp_in_len, *out, &out_len);

   st->magic_samples[channel_index] -= tmp_in_len;
   
   /* If we couldn't process all "magic" input samples, save the rest for next time */
   if (st->magic_samples[channel_index])
   {
      spx_uint32_t i;
      for (i=0;i<st->magic_samples[channel_index];i++)
         mem[N-1+i]=mem[N-1+i+tmp_in_len];
   }
   *out += out_len*st->out_stride;
   return out_len;
}