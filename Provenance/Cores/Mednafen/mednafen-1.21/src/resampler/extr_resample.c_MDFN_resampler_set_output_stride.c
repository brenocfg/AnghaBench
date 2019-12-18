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
typedef  int /*<<< orphan*/  spx_uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  out_stride; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */

void speex_resampler_set_output_stride(SpeexResamplerState *st, spx_uint32_t stride)
{
   st->out_stride = stride;
}