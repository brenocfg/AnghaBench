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
struct TYPE_5__ {TYPE_1__* codecpar; } ;
struct TYPE_4__ {int channels; int /*<<< orphan*/  channel_layout; scalar_t__ extradata; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ AVStream ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_MP1 ; 
 int /*<<< orphan*/  AV_CODEC_ID_MP2 ; 
 int /*<<< orphan*/  AV_CODEC_ID_MP3 ; 
 int AV_RL16 (scalar_t__) ; 
 int /*<<< orphan*/  AV_RL32 (scalar_t__) ; 

__attribute__((used)) static void parse_mpeg1waveformatex(AVStream *st)
{
    /* fwHeadLayer */
    switch (AV_RL16(st->codecpar->extradata)) {
    case 0x0001 : st->codecpar->codec_id = AV_CODEC_ID_MP1; break;
    case 0x0002 : st->codecpar->codec_id = AV_CODEC_ID_MP2; break;
    case 0x0004 : st->codecpar->codec_id = AV_CODEC_ID_MP3; break;
    }

    st->codecpar->bit_rate = AV_RL32(st->codecpar->extradata + 2); /* dwHeadBitrate */

    /* dwHeadMode */
    switch (AV_RL16(st->codecpar->extradata + 6)) {
    case 1 :
    case 2 :
    case 4 : st->codecpar->channels       = 2;
             st->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
             break;
    case 8 : st->codecpar->channels       = 1;
             st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
             break;
    }
}