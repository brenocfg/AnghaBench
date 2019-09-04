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
typedef  int int64_t ;

/* Variables and functions */
 int AV_CH_BACK_LEFT ; 
 int AV_CH_BACK_RIGHT ; 
 int AV_CH_FRONT_LEFT ; 
 int AV_CH_FRONT_LEFT_OF_CENTER ; 
 int AV_CH_FRONT_RIGHT ; 
 int AV_CH_FRONT_RIGHT_OF_CENTER ; 
 int AV_CH_LAYOUT_SURROUND ; 
 int AV_CH_SIDE_LEFT ; 
 int AV_CH_SIDE_RIGHT ; 
 scalar_t__ SWR_CH_MAX ; 
 scalar_t__ av_get_channel_layout_nb_channels (int) ; 
 int /*<<< orphan*/  even (int) ; 

__attribute__((used)) static int sane_layout(int64_t layout){
    if(!(layout & AV_CH_LAYOUT_SURROUND)) // at least 1 front speaker
        return 0;
    if(!even(layout & (AV_CH_FRONT_LEFT | AV_CH_FRONT_RIGHT))) // no asymetric front
        return 0;
    if(!even(layout & (AV_CH_SIDE_LEFT | AV_CH_SIDE_RIGHT)))   // no asymetric side
        return 0;
    if(!even(layout & (AV_CH_BACK_LEFT | AV_CH_BACK_RIGHT)))
        return 0;
    if(!even(layout & (AV_CH_FRONT_LEFT_OF_CENTER | AV_CH_FRONT_RIGHT_OF_CENTER)))
        return 0;
    if(av_get_channel_layout_nb_channels(layout) >= SWR_CH_MAX)
        return 0;

    return 1;
}