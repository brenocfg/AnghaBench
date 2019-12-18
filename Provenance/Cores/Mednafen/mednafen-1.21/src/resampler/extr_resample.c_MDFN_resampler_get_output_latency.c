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
struct TYPE_3__ {int filt_len; int den_rate; int num_rate; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */

int speex_resampler_get_output_latency(SpeexResamplerState *st)
{
  return ((st->filt_len / 2) * st->den_rate + (st->num_rate >> 1)) / st->num_rate;
}