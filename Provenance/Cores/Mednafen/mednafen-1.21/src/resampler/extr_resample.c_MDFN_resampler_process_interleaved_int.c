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
typedef  int /*<<< orphan*/  spx_int16_t ;
struct TYPE_4__ {int in_stride; int out_stride; int nb_channels; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 int RESAMPLER_ERR_SUCCESS ; 
 int /*<<< orphan*/  speex_resampler_process_int (TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 

int speex_resampler_process_interleaved_int(SpeexResamplerState *st, const spx_int16_t *in, spx_uint32_t *in_len, spx_int16_t *out, spx_uint32_t *out_len)
{
   spx_uint32_t i;
   int istride_save, ostride_save;
   spx_uint32_t bak_len = *out_len;
   istride_save = st->in_stride;
   ostride_save = st->out_stride;
   st->in_stride = st->out_stride = st->nb_channels;
   for (i=0;i<st->nb_channels;i++)
   {
      *out_len = bak_len;
      if (in != NULL)
         speex_resampler_process_int(st, i, in+i, in_len, out+i, out_len);
      else
         speex_resampler_process_int(st, i, NULL, in_len, out+i, out_len);
   }
   st->in_stride = istride_save;
   st->out_stride = ostride_save;
   return RESAMPLER_ERR_SUCCESS;
}