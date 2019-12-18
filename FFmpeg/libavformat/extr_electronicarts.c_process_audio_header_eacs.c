#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int bytes; int /*<<< orphan*/  audio_codec; void* num_channels; scalar_t__ big_endian; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_1__ EaDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_IMA_EA_EACS ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_MULAW ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16LE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S8 ; 
 void* avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_2__*,char*,int) ; 

__attribute__((used)) static void process_audio_header_eacs(AVFormatContext *s)
{
    EaDemuxContext *ea = s->priv_data;
    AVIOContext *pb    = s->pb;
    int compression_type;

    ea->sample_rate  = ea->big_endian ? avio_rb32(pb) : avio_rl32(pb);
    ea->bytes        = avio_r8(pb);   /* 1=8-bit, 2=16-bit */
    ea->num_channels = avio_r8(pb);
    compression_type = avio_r8(pb);
    avio_skip(pb, 13);

    switch (compression_type) {
    case 0:
        switch (ea->bytes) {
        case 1:
            ea->audio_codec = AV_CODEC_ID_PCM_S8;
            break;
        case 2:
            ea->audio_codec = AV_CODEC_ID_PCM_S16LE;
            break;
        }
        break;
    case 1:
        ea->audio_codec = AV_CODEC_ID_PCM_MULAW;
        ea->bytes       = 1;
        break;
    case 2:
        ea->audio_codec = AV_CODEC_ID_ADPCM_IMA_EA_EACS;
        break;
    default:
        avpriv_request_sample(s,
                              "stream type; audio compression_type=%i",
                              compression_type);
    }
}