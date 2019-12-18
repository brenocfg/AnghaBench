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
typedef  int UINT8 ;

/* Variables and functions */
#define  A2D_SBC_IE_CH_MD_DUAL 131 
#define  A2D_SBC_IE_CH_MD_JOINT 130 
#define  A2D_SBC_IE_CH_MD_MONO 129 
#define  A2D_SBC_IE_CH_MD_STEREO 128 

__attribute__((used)) static int btc_a2dp_sink_get_track_channel_count(UINT8 channeltype)
{
    int count = 1;
    switch (channeltype) {
    case A2D_SBC_IE_CH_MD_MONO:
        count = 1;
        break;
    case A2D_SBC_IE_CH_MD_DUAL:
    case A2D_SBC_IE_CH_MD_STEREO:
    case A2D_SBC_IE_CH_MD_JOINT:
        count = 2;
        break;
    }
    return count;
}