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
struct TYPE_15__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_14__ {scalar_t__ start_time; TYPE_1__* codecpar; } ;
struct TYPE_13__ {int dss_header_size; int /*<<< orphan*/  dss_sp_buf; scalar_t__ swap; scalar_t__ counter; void* audio_codec; } ;
struct TYPE_12__ {int sample_rate; int channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ DSSDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_DSS_SP ; 
 int /*<<< orphan*/  AV_CODEC_ID_G723_1 ; 
 void* DSS_ACODEC_DSS_SP ; 
 void* DSS_ACODEC_G723_1 ; 
 int /*<<< orphan*/  DSS_AUTHOR_SIZE ; 
 int DSS_BLOCK_SIZE ; 
 int /*<<< orphan*/  DSS_COMMENT_SIZE ; 
 scalar_t__ DSS_FRAME_SIZE ; 
 int DSS_HEAD_OFFSET_ACODEC ; 
 int /*<<< orphan*/  DSS_HEAD_OFFSET_AUTHOR ; 
 int /*<<< orphan*/  DSS_HEAD_OFFSET_COMMENT ; 
 int /*<<< orphan*/  DSS_HEAD_OFFSET_END_TIME ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_malloc (scalar_t__) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 void* avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*,void*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int dss_read_metadata_date (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int dss_read_metadata_string (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dss_read_header(AVFormatContext *s)
{
    DSSDemuxContext *ctx = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st;
    int ret, version;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    version = avio_r8(pb);
    ctx->dss_header_size = version * DSS_BLOCK_SIZE;

    ret = dss_read_metadata_string(s, DSS_HEAD_OFFSET_AUTHOR,
                                   DSS_AUTHOR_SIZE, "author");
    if (ret)
        return ret;

    ret = dss_read_metadata_date(s, DSS_HEAD_OFFSET_END_TIME, "date");
    if (ret)
        return ret;

    ret = dss_read_metadata_string(s, DSS_HEAD_OFFSET_COMMENT,
                                   DSS_COMMENT_SIZE, "comment");
    if (ret)
        return ret;

    avio_seek(pb, DSS_HEAD_OFFSET_ACODEC, SEEK_SET);
    ctx->audio_codec = avio_r8(pb);

    if (ctx->audio_codec == DSS_ACODEC_DSS_SP) {
        st->codecpar->codec_id    = AV_CODEC_ID_DSS_SP;
        st->codecpar->sample_rate = 11025;
    } else if (ctx->audio_codec == DSS_ACODEC_G723_1) {
        st->codecpar->codec_id    = AV_CODEC_ID_G723_1;
        st->codecpar->sample_rate = 8000;
    } else {
        avpriv_request_sample(s, "Support for codec %x in DSS",
                              ctx->audio_codec);
        return AVERROR_PATCHWELCOME;
    }

    st->codecpar->codec_type     = AVMEDIA_TYPE_AUDIO;
    st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
    st->codecpar->channels       = 1;

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);
    st->start_time = 0;

    /* Jump over header */

    if (avio_seek(pb, ctx->dss_header_size, SEEK_SET) != ctx->dss_header_size)
        return AVERROR(EIO);

    ctx->counter = 0;
    ctx->swap    = 0;

    ctx->dss_sp_buf = av_malloc(DSS_FRAME_SIZE + 1);
    if (!ctx->dss_sp_buf)
        return AVERROR(ENOMEM);

    return 0;
}