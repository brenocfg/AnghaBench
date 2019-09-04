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
struct TYPE_4__ {long long den; long long num; } ;
struct TYPE_5__ {scalar_t__ codec_tag; scalar_t__ codec_id; TYPE_1__ time_base; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_GIF ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_HEVC ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_RL32 (char*) ; 

__attribute__((used)) static int tb_unreliable(AVCodecContext *c)
{
    if (c->time_base.den >= 101LL * c->time_base.num ||
        c->time_base.den <    5LL * c->time_base.num ||
        // c->codec_tag == AV_RL32("DIVX") ||
        // c->codec_tag == AV_RL32("XVID") ||
        c->codec_tag == AV_RL32("mp4v") ||
        c->codec_id == AV_CODEC_ID_MPEG2VIDEO ||
        c->codec_id == AV_CODEC_ID_GIF ||
        c->codec_id == AV_CODEC_ID_HEVC ||
        c->codec_id == AV_CODEC_ID_H264)
        return 1;
    return 0;
}