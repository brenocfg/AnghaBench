#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ channel_layout; } ;
struct TYPE_5__ {scalar_t__ channel_layout; } ;
struct TYPE_7__ {TYPE_2__ in; TYPE_1__ out; } ;
typedef  TYPE_3__ hb_audio_resample_t ;

/* Variables and functions */
 scalar_t__ AV_CH_LAYOUT_MONO ; 
 scalar_t__ AV_CH_LAYOUT_STEREO ; 
 scalar_t__ AV_CH_LAYOUT_STEREO_DOWNMIX ; 
 scalar_t__ is_mono (scalar_t__) ; 

void hb_audio_resample_set_channel_layout(hb_audio_resample_t *resample,
                                          uint64_t channel_layout)
{
    if (resample != NULL)
    {
        if (channel_layout == AV_CH_LAYOUT_STEREO_DOWNMIX)
        {
            // Dolby Surround is Stereo when it comes to remixing
            channel_layout = AV_CH_LAYOUT_STEREO;
        }
        // swresample can't remap a single-channel layout to
        // another single-channel layout
        if (resample->out.channel_layout == AV_CH_LAYOUT_MONO &&
            is_mono(channel_layout))
        {
            channel_layout = AV_CH_LAYOUT_MONO;
        }
        resample->in.channel_layout = channel_layout;
    }
}