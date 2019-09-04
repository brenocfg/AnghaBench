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
struct TYPE_3__ {scalar_t__ channels; void** map; } ;
typedef  TYPE_1__ pa_channel_map ;
typedef  int int64_t ;

/* Variables and functions */
 int AV_CH_BACK_CENTER ; 
 int AV_CH_BACK_LEFT ; 
 int AV_CH_BACK_RIGHT ; 
 int AV_CH_FRONT_CENTER ; 
 int AV_CH_FRONT_LEFT ; 
 int AV_CH_FRONT_LEFT_OF_CENTER ; 
 int AV_CH_FRONT_RIGHT ; 
 int AV_CH_FRONT_RIGHT_OF_CENTER ; 
 int AV_CH_LOW_FREQUENCY ; 
 int AV_CH_LOW_FREQUENCY_2 ; 
 int AV_CH_SIDE_LEFT ; 
 int AV_CH_SIDE_RIGHT ; 
 int AV_CH_STEREO_LEFT ; 
 int AV_CH_STEREO_RIGHT ; 
 int AV_CH_SURROUND_DIRECT_LEFT ; 
 int AV_CH_SURROUND_DIRECT_RIGHT ; 
 int AV_CH_TOP_BACK_CENTER ; 
 int AV_CH_TOP_BACK_LEFT ; 
 int AV_CH_TOP_BACK_RIGHT ; 
 int AV_CH_TOP_CENTER ; 
 int AV_CH_TOP_FRONT_CENTER ; 
 int AV_CH_TOP_FRONT_LEFT ; 
 int AV_CH_TOP_FRONT_RIGHT ; 
 int AV_CH_WIDE_LEFT ; 
 int AV_CH_WIDE_RIGHT ; 
 void* PA_CHANNEL_POSITION_AUX0 ; 
 void* PA_CHANNEL_POSITION_AUX1 ; 
 void* PA_CHANNEL_POSITION_AUX2 ; 
 void* PA_CHANNEL_POSITION_AUX3 ; 
 void* PA_CHANNEL_POSITION_FRONT_CENTER ; 
 void* PA_CHANNEL_POSITION_FRONT_LEFT ; 
 void* PA_CHANNEL_POSITION_FRONT_LEFT_OF_CENTER ; 
 void* PA_CHANNEL_POSITION_FRONT_RIGHT ; 
 void* PA_CHANNEL_POSITION_FRONT_RIGHT_OF_CENTER ; 
 void* PA_CHANNEL_POSITION_LFE ; 
 void* PA_CHANNEL_POSITION_REAR_CENTER ; 
 void* PA_CHANNEL_POSITION_REAR_LEFT ; 
 void* PA_CHANNEL_POSITION_REAR_RIGHT ; 
 void* PA_CHANNEL_POSITION_SIDE_LEFT ; 
 void* PA_CHANNEL_POSITION_SIDE_RIGHT ; 
 void* PA_CHANNEL_POSITION_TOP_CENTER ; 
 void* PA_CHANNEL_POSITION_TOP_FRONT_CENTER ; 
 void* PA_CHANNEL_POSITION_TOP_FRONT_LEFT ; 
 void* PA_CHANNEL_POSITION_TOP_FRONT_RIGHT ; 
 void* PA_CHANNEL_POSITION_TOP_REAR_CENTER ; 
 void* PA_CHANNEL_POSITION_TOP_REAR_LEFT ; 
 void* PA_CHANNEL_POSITION_TOP_REAR_RIGHT ; 

__attribute__((used)) static void pulse_map_channels_to_pulse(int64_t channel_layout, pa_channel_map *channel_map)
{
    channel_map->channels = 0;
    if (channel_layout & AV_CH_FRONT_LEFT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_FRONT_LEFT;
    if (channel_layout & AV_CH_FRONT_RIGHT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_FRONT_RIGHT;
    if (channel_layout & AV_CH_FRONT_CENTER)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_FRONT_CENTER;
    if (channel_layout & AV_CH_LOW_FREQUENCY)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_LFE;
    if (channel_layout & AV_CH_BACK_LEFT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_REAR_LEFT;
    if (channel_layout & AV_CH_BACK_RIGHT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_REAR_RIGHT;
    if (channel_layout & AV_CH_FRONT_LEFT_OF_CENTER)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_FRONT_LEFT_OF_CENTER;
    if (channel_layout & AV_CH_FRONT_RIGHT_OF_CENTER)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_FRONT_RIGHT_OF_CENTER;
    if (channel_layout & AV_CH_BACK_CENTER)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_REAR_CENTER;
    if (channel_layout & AV_CH_SIDE_LEFT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_SIDE_LEFT;
    if (channel_layout & AV_CH_SIDE_RIGHT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_SIDE_RIGHT;
    if (channel_layout & AV_CH_TOP_CENTER)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_TOP_CENTER;
    if (channel_layout & AV_CH_TOP_FRONT_LEFT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_TOP_FRONT_LEFT;
    if (channel_layout & AV_CH_TOP_FRONT_CENTER)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_TOP_FRONT_CENTER;
    if (channel_layout & AV_CH_TOP_FRONT_RIGHT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_TOP_FRONT_RIGHT;
    if (channel_layout & AV_CH_TOP_BACK_LEFT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_TOP_REAR_LEFT;
    if (channel_layout & AV_CH_TOP_BACK_CENTER)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_TOP_REAR_CENTER;
    if (channel_layout & AV_CH_TOP_BACK_RIGHT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_TOP_REAR_RIGHT;
    if (channel_layout & AV_CH_STEREO_LEFT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_FRONT_LEFT;
    if (channel_layout & AV_CH_STEREO_RIGHT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_FRONT_RIGHT;
    if (channel_layout & AV_CH_WIDE_LEFT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_AUX0;
    if (channel_layout & AV_CH_WIDE_RIGHT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_AUX1;
    if (channel_layout & AV_CH_SURROUND_DIRECT_LEFT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_AUX2;
    if (channel_layout & AV_CH_SURROUND_DIRECT_RIGHT)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_AUX3;
    if (channel_layout & AV_CH_LOW_FREQUENCY_2)
        channel_map->map[channel_map->channels++] = PA_CHANNEL_POSITION_LFE;
}