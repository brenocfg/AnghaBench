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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct MovChannelLayoutMap {int tag; int layout; } ;

/* Variables and functions */
 int MOV_CH_LAYOUT_USE_BITMAP ; 
 int MOV_CH_LAYOUT_USE_DESCRIPTIONS ; 
 struct MovChannelLayoutMap** mov_ch_layout_map ; 

uint64_t ff_mov_get_channel_layout(uint32_t tag, uint32_t bitmap)
{
    int i, channels;
    const struct MovChannelLayoutMap *layout_map;

    /* use ff_mov_get_channel_label() to build a layout instead */
    if (tag == MOV_CH_LAYOUT_USE_DESCRIPTIONS)
        return 0;

    /* handle the use of the channel bitmap */
    if (tag == MOV_CH_LAYOUT_USE_BITMAP)
        return bitmap < 0x40000 ? bitmap : 0;

    /* get the layout map based on the channel count for the specified layout tag */
    channels = tag & 0xFFFF;
    if (channels > 9)
        channels = 0;
    layout_map = mov_ch_layout_map[channels];

    /* find the channel layout for the specified layout tag */
    for (i = 0; layout_map[i].tag != 0; i++) {
        if (layout_map[i].tag == tag)
            break;
    }
    return layout_map[i].layout;
}