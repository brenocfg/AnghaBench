#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spx_uint32_t ;
typedef  int /*<<< orphan*/  SpeexResamplerState ;

/* Variables and functions */
 int speex_resampler_set_rate_frac (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int speex_resampler_set_rate(SpeexResamplerState *st, spx_uint32_t in_rate, spx_uint32_t out_rate)
{
   return speex_resampler_set_rate_frac(st, in_rate, out_rate, in_rate, out_rate);
}