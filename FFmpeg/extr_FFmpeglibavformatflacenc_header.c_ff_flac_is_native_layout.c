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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ AV_CH_LAYOUT_5POINT0 ; 
 scalar_t__ AV_CH_LAYOUT_5POINT1 ; 
 scalar_t__ AV_CH_LAYOUT_6POINT1 ; 
 scalar_t__ AV_CH_LAYOUT_7POINT1 ; 
 scalar_t__ AV_CH_LAYOUT_MONO ; 
 scalar_t__ AV_CH_LAYOUT_QUAD ; 
 scalar_t__ AV_CH_LAYOUT_STEREO ; 
 scalar_t__ AV_CH_LAYOUT_SURROUND ; 

int ff_flac_is_native_layout(uint64_t channel_layout)
{
    if (channel_layout == AV_CH_LAYOUT_MONO     ||
        channel_layout == AV_CH_LAYOUT_STEREO   ||
        channel_layout == AV_CH_LAYOUT_SURROUND ||
        channel_layout == AV_CH_LAYOUT_QUAD     ||
        channel_layout == AV_CH_LAYOUT_5POINT0  ||
        channel_layout == AV_CH_LAYOUT_5POINT1  ||
        channel_layout == AV_CH_LAYOUT_6POINT1  ||
        channel_layout == AV_CH_LAYOUT_7POINT1)
        return 1;
    return 0;
}