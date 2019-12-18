#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double lfe_mix_level; double center_mix_level; double surround_mix_level; } ;
struct TYPE_5__ {TYPE_1__ in; } ;
typedef  TYPE_2__ hb_audio_resample_t ;

/* Variables and functions */

void hb_audio_resample_set_mix_levels(hb_audio_resample_t *resample,
                                      double surround_mix_level,
                                      double center_mix_level,
                                      double lfe_mix_level)
{
    if (resample != NULL)
    {
        resample->in.lfe_mix_level      = lfe_mix_level;
        resample->in.center_mix_level   = center_mix_level;
        resample->in.surround_mix_level = surround_mix_level;
    }
}