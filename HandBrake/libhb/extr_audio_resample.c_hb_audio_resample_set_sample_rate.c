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
struct TYPE_4__ {int sample_rate; } ;
struct TYPE_5__ {TYPE_1__ in; } ;
typedef  TYPE_2__ hb_audio_resample_t ;

/* Variables and functions */

void hb_audio_resample_set_sample_rate(hb_audio_resample_t *resample,
                                       int sample_rate)
{
    if (resample != NULL)
    {
        resample->in.sample_rate = sample_rate;
    }
}