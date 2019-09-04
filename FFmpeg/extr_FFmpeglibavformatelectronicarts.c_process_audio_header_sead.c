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
struct TYPE_5__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  audio_codec; void* num_channels; void* bytes; void* sample_rate; } ;
typedef  TYPE_1__ EaDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_IMA_EA_SEAD ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_audio_header_sead(AVFormatContext *s)
{
    EaDemuxContext *ea = s->priv_data;
    AVIOContext *pb    = s->pb;

    ea->sample_rate  = avio_rl32(pb);
    ea->bytes        = avio_rl32(pb);  /* 1=8-bit, 2=16-bit */
    ea->num_channels = avio_rl32(pb);
    ea->audio_codec  = AV_CODEC_ID_ADPCM_IMA_EA_SEAD;
}