#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  long long int64_t ;
struct TYPE_15__ {TYPE_1__* iformat; int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; } ;
struct TYPE_14__ {TYPE_2__* codecpar; } ;
struct TYPE_13__ {int sample_rate; int channels; long long bit_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_12__ {int /*<<< orphan*/  raw_codec_id; } ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int AV_TIMECODE_STR_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  av_timecode_make_smpte_tc_string (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  get_metadata (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  wsd_to_av_channel_layoyt (TYPE_4__*,int) ; 

__attribute__((used)) static int wsd_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    AVStream *st;
    int version;
    uint32_t text_offset, data_offset, channel_assign;
    char playback_time[AV_TIMECODE_STR_SIZE];

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avio_skip(pb, 8);
    version = avio_r8(pb);
    av_log(s, AV_LOG_DEBUG, "version: %i.%i\n", version >> 4, version & 0xF);
    avio_skip(pb, 11);

    if (version < 0x10) {
        text_offset = 0x80;
        data_offset = 0x800;
        avio_skip(pb, 8);
    } else {
        text_offset = avio_rb32(pb);
        data_offset = avio_rb32(pb);
    }

    avio_skip(pb, 4);
    av_timecode_make_smpte_tc_string(playback_time, avio_rb32(pb), 0);
    av_dict_set(&s->metadata, "playback_time", playback_time, 0);

    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id    = s->iformat->raw_codec_id;
    st->codecpar->sample_rate = avio_rb32(pb) / 8;
    avio_skip(pb, 4);
    st->codecpar->channels    = avio_r8(pb) & 0xF;
    st->codecpar->bit_rate    = (int64_t)st->codecpar->channels * st->codecpar->sample_rate * 8LL;
    if (!st->codecpar->channels)
        return AVERROR_INVALIDDATA;

    avio_skip(pb, 3);
    channel_assign         = avio_rb32(pb);
    if (!(channel_assign & 1)) {
        int i;
        for (i = 1; i < 32; i++)
            if ((channel_assign >> i) & 1)
                st->codecpar->channel_layout |= wsd_to_av_channel_layoyt(s, i);
    }

    avio_skip(pb, 16);
    if (avio_rb32(pb))
       avpriv_request_sample(s, "emphasis");

    if (avio_seek(pb, text_offset, SEEK_SET) >= 0) {
        get_metadata(s, "title",       128);
        get_metadata(s, "composer",    128);
        get_metadata(s, "song_writer", 128);
        get_metadata(s, "artist",      128);
        get_metadata(s, "album",       128);
        get_metadata(s, "genre",        32);
        get_metadata(s, "date",         32);
        get_metadata(s, "location",     32);
        get_metadata(s, "comment",     512);
        get_metadata(s, "user",        512);
    }

    return avio_seek(pb, data_offset, SEEK_SET);
}