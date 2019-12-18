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
typedef  int spx_uint32_t ;
struct TYPE_3__ {int nb_channels; int filt_len; scalar_t__* mem; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 int RESAMPLER_ERR_SUCCESS ; 

int speex_resampler_reset_mem(SpeexResamplerState *st)
{
   spx_uint32_t i;
   for (i=0;i<st->nb_channels*(st->filt_len-1);i++)
      st->mem[i] = 0;
   return RESAMPLER_ERR_SUCCESS;
}