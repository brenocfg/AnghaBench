#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_28__ {TYPE_3__* pb; TYPE_1__* priv_data; } ;
struct TYPE_27__ {int seekable; } ;
struct TYPE_26__ {int duration; TYPE_10__* codecpar; scalar_t__ start_time; } ;
struct TYPE_25__ {int header_pos; int ver; int samples; int /*<<< orphan*/  apetag_start; } ;
struct TYPE_24__ {int bits_per_coded_sample; int channels; int* extradata; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_1__ MPCContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_MUSEPACK8 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TAG_MPCK ; 
 int TAG_STREAMHDR ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_feof (TYPE_3__*) ; 
 int avio_r8 (TYPE_3__*) ; 
 scalar_t__ avio_rl32 (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (TYPE_3__*,int) ; 
 int avio_tell (TYPE_3__*) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_ape_parse_tag (TYPE_4__*) ; 
 scalar_t__ ff_get_extradata (TYPE_4__*,TYPE_10__*,TYPE_3__*,int) ; 
 int ffio_read_varlen (TYPE_3__*) ; 
 int /*<<< orphan*/  mpc8_get_chunk_header (TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  mpc8_handle_chunk (TYPE_4__*,int,int,int) ; 
 int /*<<< orphan*/ * mpc8_rate ; 

__attribute__((used)) static int mpc8_read_header(AVFormatContext *s)
{
    MPCContext *c = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st;
    int tag = 0;
    int64_t size, pos;

    c->header_pos = avio_tell(pb);
    if(avio_rl32(pb) != TAG_MPCK){
        av_log(s, AV_LOG_ERROR, "Not a Musepack8 file\n");
        return AVERROR_INVALIDDATA;
    }

    while(!avio_feof(pb)){
        pos = avio_tell(pb);
        mpc8_get_chunk_header(pb, &tag, &size);
        if (size < 0) {
            av_log(s, AV_LOG_ERROR, "Invalid chunk length\n");
            return AVERROR_INVALIDDATA;
        }
        if(tag == TAG_STREAMHDR)
            break;
        mpc8_handle_chunk(s, tag, pos, size);
    }
    if(tag != TAG_STREAMHDR){
        av_log(s, AV_LOG_ERROR, "Stream header not found\n");
        return AVERROR_INVALIDDATA;
    }
    pos = avio_tell(pb);
    avio_skip(pb, 4); //CRC
    c->ver = avio_r8(pb);
    if(c->ver != 8){
        avpriv_report_missing_feature(s, "Stream version %d", c->ver);
        return AVERROR_PATCHWELCOME;
    }
    c->samples = ffio_read_varlen(pb);
    ffio_read_varlen(pb); //silence samples at the beginning

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_MUSEPACK8;
    st->codecpar->bits_per_coded_sample = 16;

    if (ff_get_extradata(s, st->codecpar, pb, 2) < 0)
        return AVERROR(ENOMEM);

    st->codecpar->channels = (st->codecpar->extradata[1] >> 4) + 1;
    st->codecpar->sample_rate = mpc8_rate[st->codecpar->extradata[0] >> 5];
    avpriv_set_pts_info(st, 32, 1152  << (st->codecpar->extradata[1]&3)*2, st->codecpar->sample_rate);
    st->start_time = 0;
    st->duration = c->samples / (1152 << (st->codecpar->extradata[1]&3)*2);
    size -= avio_tell(pb) - pos;
    if (size > 0)
        avio_skip(pb, size);

    if (pb->seekable & AVIO_SEEKABLE_NORMAL) {
        int64_t pos = avio_tell(s->pb);
        c->apetag_start = ff_ape_parse_tag(s);
        avio_seek(s->pb, pos, SEEK_SET);
    }

    return 0;
}