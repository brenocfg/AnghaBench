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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int remap_needed; int nchannels; scalar_t__ channel_map_in; scalar_t__ channel_map_out; int* table; } ;
typedef  TYPE_1__ hb_audio_remap_t ;

/* Variables and functions */
 scalar_t__ AV_CH_LAYOUT_STEREO ; 
 scalar_t__ AV_CH_LAYOUT_STEREO_DOWNMIX ; 
 int HB_AUDIO_REMAP_MAX_CHANNELS ; 
 int av_get_channel_layout_nb_channels (scalar_t__) ; 
 int /*<<< orphan*/  hb_audio_remap_build_table (scalar_t__,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  hb_log (char*,int) ; 

void hb_audio_remap_set_channel_layout(hb_audio_remap_t *remap,
                                       uint64_t channel_layout)
{
    if (remap != NULL)
    {
        int ii;
        remap->remap_needed = 0;

        // sanitize the layout
        if (channel_layout == AV_CH_LAYOUT_STEREO_DOWNMIX)
        {
            channel_layout = AV_CH_LAYOUT_STEREO;
        }
        remap->nchannels = av_get_channel_layout_nb_channels(channel_layout);

        // in some cases, remapping is not necessary and/or supported
        if (remap->nchannels > HB_AUDIO_REMAP_MAX_CHANNELS)
        {
            hb_log("hb_audio_remap_set_channel_layout: too many channels (%d)",
                   remap->nchannels);
            return;
        }
        if (remap->channel_map_in == remap->channel_map_out)
        {
            return;
        }

        // build the table and check whether remapping is necessary
        hb_audio_remap_build_table(remap->channel_map_out,
                                   remap->channel_map_in, channel_layout,
                                   remap->table);
        for (ii = 0; ii < remap->nchannels; ii++)
        {
            if (remap->table[ii] != ii)
            {
                remap->remap_needed = 1;
                break;
            }
        }
    }
}