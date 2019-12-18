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
struct TYPE_4__ {int quality; scalar_t__ initialised; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 int RESAMPLER_ERR_INVALID_ARG ; 
 int RESAMPLER_ERR_SUCCESS ; 
 int /*<<< orphan*/  update_filter (TYPE_1__*) ; 

int speex_resampler_set_quality(SpeexResamplerState *st, int quality)
{
   if (quality > 10 || quality < 0)
      return RESAMPLER_ERR_INVALID_ARG;
   if (st->quality == quality)
      return RESAMPLER_ERR_SUCCESS;
   st->quality = quality;
   if (st->initialised)
      update_filter(st);
   return RESAMPLER_ERR_SUCCESS;
}