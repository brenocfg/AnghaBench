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
typedef  int uint64_t ;
struct TYPE_4__ {int* channel_order_map; } ;
typedef  TYPE_1__ hb_chan_map_t ;

/* Variables and functions */
 int AV_CH_LAYOUT_STEREO ; 
 int AV_CH_LAYOUT_STEREO_DOWNMIX ; 
 int av_get_channel_layout_nb_channels (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void hb_audio_remap_build_table(hb_chan_map_t *channel_map_out,
                                hb_chan_map_t *channel_map_in,
                                uint64_t channel_layout,
                                int *remap_table)
{
    int ii, jj, nchannels, out_chan_idx, remap_idx;
    uint64_t *channels_in, *channels_out;

    if (channel_layout == AV_CH_LAYOUT_STEREO_DOWNMIX)
    {
        // Dolby Surround is Stereo when it comes to remapping
        channel_layout = AV_CH_LAYOUT_STEREO;
    }
    nchannels = av_get_channel_layout_nb_channels(channel_layout);

    // clear remap table before (re-)building it
    memset(remap_table, 0, nchannels * sizeof(int));

    out_chan_idx = 0;
    channels_in  = channel_map_in ->channel_order_map;
    channels_out = channel_map_out->channel_order_map;
    for (ii = 0; channels_out[ii] && out_chan_idx < nchannels; ii++)
    {
        if (channel_layout & channels_out[ii])
        {
            remap_idx = 0;
            for (jj = 0; channels_in[jj] && remap_idx < nchannels; jj++)
            {
                if (channels_out[ii] == channels_in[jj])
                {
                    remap_table[out_chan_idx++] = remap_idx++;
                    break;
                }
                else if (channel_layout & channels_in[jj])
                {
                    remap_idx++;
                }
            }
        }
    }
}