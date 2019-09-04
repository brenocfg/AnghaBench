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

/* Variables and functions */
#define  AV_CH_LAYOUT_4POINT0 140 
#define  AV_CH_LAYOUT_5POINT0 139 
#define  AV_CH_LAYOUT_5POINT1 138 
#define  AV_CH_LAYOUT_6POINT0 137 
#define  AV_CH_LAYOUT_6POINT1 136 
#define  AV_CH_LAYOUT_7POINT0 135 
#define  AV_CH_LAYOUT_7POINT1 134 
#define  AV_CH_LAYOUT_7POINT1_WIDE_BACK 133 
#define  AV_CH_LAYOUT_MONO 132 
#define  AV_CH_LAYOUT_OCTAGONAL 131 
#define  AV_CH_LAYOUT_QUAD 130 
#define  AV_CH_LAYOUT_STEREO 129 
#define  AV_CH_LAYOUT_SURROUND 128 
 int kAudioChannelLayoutTag_AAC_3_0 ; 
 int kAudioChannelLayoutTag_AAC_4_0 ; 
 int kAudioChannelLayoutTag_AAC_5_0 ; 
 int kAudioChannelLayoutTag_AAC_5_1 ; 
 int kAudioChannelLayoutTag_AAC_6_0 ; 
 int kAudioChannelLayoutTag_AAC_6_1 ; 
 int kAudioChannelLayoutTag_AAC_7_0 ; 
 int kAudioChannelLayoutTag_AAC_7_1 ; 
 int kAudioChannelLayoutTag_AAC_Octagonal ; 
 int kAudioChannelLayoutTag_AAC_Quadraphonic ; 
 int kAudioChannelLayoutTag_MPEG_7_1_C ; 
 int kAudioChannelLayoutTag_Mono ; 
 int kAudioChannelLayoutTag_Stereo ; 

__attribute__((used)) static int get_aac_tag(uint64_t in_layout)
{
    switch (in_layout) {
    case AV_CH_LAYOUT_MONO:
        return kAudioChannelLayoutTag_Mono;
    case AV_CH_LAYOUT_STEREO:
        return kAudioChannelLayoutTag_Stereo;
    case AV_CH_LAYOUT_QUAD:
        return kAudioChannelLayoutTag_AAC_Quadraphonic;
    case AV_CH_LAYOUT_OCTAGONAL:
        return kAudioChannelLayoutTag_AAC_Octagonal;
    case AV_CH_LAYOUT_SURROUND:
        return kAudioChannelLayoutTag_AAC_3_0;
    case AV_CH_LAYOUT_4POINT0:
        return kAudioChannelLayoutTag_AAC_4_0;
    case AV_CH_LAYOUT_5POINT0:
        return kAudioChannelLayoutTag_AAC_5_0;
    case AV_CH_LAYOUT_5POINT1:
        return kAudioChannelLayoutTag_AAC_5_1;
    case AV_CH_LAYOUT_6POINT0:
        return kAudioChannelLayoutTag_AAC_6_0;
    case AV_CH_LAYOUT_6POINT1:
        return kAudioChannelLayoutTag_AAC_6_1;
    case AV_CH_LAYOUT_7POINT0:
        return kAudioChannelLayoutTag_AAC_7_0;
    case AV_CH_LAYOUT_7POINT1_WIDE_BACK:
        return kAudioChannelLayoutTag_AAC_7_1;
    case AV_CH_LAYOUT_7POINT1:
        return kAudioChannelLayoutTag_MPEG_7_1_C;
    default:
        return 0;
    }
}