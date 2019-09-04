#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int channels; int block_align; void* sample_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  extradata; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  codec_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  pb; } ;
struct TYPE_10__ {TYPE_4__* codecpar; int /*<<< orphan*/  duration; int /*<<< orphan*/  need_parsing; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL_RAW ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_PSX ; 
 int /*<<< orphan*/  AV_CODEC_ID_ATRAC3 ; 
 int /*<<< orphan*/  AV_CODEC_ID_MP3 ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16BE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16LE ; 
 int /*<<< orphan*/  AV_WL16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_get_audio_frame_duration2 (TYPE_4__*,unsigned int) ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_2__*,char*,unsigned int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,void*) ; 
 int ff_alloc_extradata (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msf_read_header(AVFormatContext *s)
{
    unsigned codec, size;
    AVStream *st;
    int ret;

    avio_skip(s->pb, 4);

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    codec                  = avio_rb32(s->pb);
    st->codecpar->channels    = avio_rb32(s->pb);
    if (st->codecpar->channels <= 0 || st->codecpar->channels >= INT_MAX / 1024)
        return AVERROR_INVALIDDATA;
    size = avio_rb32(s->pb);
    st->codecpar->sample_rate = avio_rb32(s->pb);
    if (st->codecpar->sample_rate <= 0)
        return AVERROR_INVALIDDATA;
    // avio_rb32(s->pb); /* byte flags with encoder info */
    switch (codec) {
    case 0: st->codecpar->codec_id = AV_CODEC_ID_PCM_S16BE; break;
    case 1: st->codecpar->codec_id = AV_CODEC_ID_PCM_S16LE; break;
    case 3: st->codecpar->block_align = 16 * st->codecpar->channels;
            st->codecpar->codec_id = AV_CODEC_ID_ADPCM_PSX; break;
    case 4:
    case 5:
    case 6: st->codecpar->block_align = (codec == 4 ? 96 : codec == 5 ? 152 : 192) * st->codecpar->channels;
            ret = ff_alloc_extradata(st->codecpar, 14);
            if (ret < 0)
                return ret;
            memset(st->codecpar->extradata, 0, st->codecpar->extradata_size);
            AV_WL16(st->codecpar->extradata, 1); /* version */
            AV_WL16(st->codecpar->extradata+2, 2048 * st->codecpar->channels); /* unknown size */
            AV_WL16(st->codecpar->extradata+6, codec == 4 ? 1 : 0); /* joint stereo */
            AV_WL16(st->codecpar->extradata+8, codec == 4 ? 1 : 0); /* joint stereo (repeat?) */
            AV_WL16(st->codecpar->extradata+10, 1);
            st->codecpar->codec_id = AV_CODEC_ID_ATRAC3;    break;
    case 7: st->need_parsing = AVSTREAM_PARSE_FULL_RAW;
            st->codecpar->codec_id = AV_CODEC_ID_MP3;       break;
    default:
            avpriv_request_sample(s, "Codec %d", codec);
            return AVERROR_PATCHWELCOME;
    }
    st->duration = av_get_audio_frame_duration2(st->codecpar, size);
    avio_skip(s->pb, 0x40 - avio_tell(s->pb));
    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}