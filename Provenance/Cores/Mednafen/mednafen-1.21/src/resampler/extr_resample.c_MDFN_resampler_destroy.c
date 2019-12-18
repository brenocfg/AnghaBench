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
struct TYPE_4__ {struct TYPE_4__* samp_frac_num; struct TYPE_4__* magic_samples; struct TYPE_4__* last_sample; struct TYPE_4__* sinc_table; struct TYPE_4__* mem; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 int /*<<< orphan*/  speex_free (TYPE_1__*) ; 

void speex_resampler_destroy(SpeexResamplerState *st)
{
   speex_free(st->mem);
   speex_free(st->sinc_table);
   speex_free(st->last_sample);
   speex_free(st->magic_samples);
   speex_free(st->samp_frac_num);
   speex_free(st);
}