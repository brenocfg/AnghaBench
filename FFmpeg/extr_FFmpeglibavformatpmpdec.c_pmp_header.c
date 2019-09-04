#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  long long uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_14__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_13__ {long long nb_frames; long long duration; TYPE_1__* codecpar; } ;
struct TYPE_12__ {int num_streams; } ;
struct TYPE_11__ {int codec_id; int width; int height; int channels; int sample_rate; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ PMPContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVINDEX_KEYFRAME ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int AV_CODEC_ID_AAC ; 
 int AV_CODEC_ID_H264 ; 
 int AV_CODEC_ID_MP3 ; 
 int AV_CODEC_ID_MPEG4 ; 
 int AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_add_index_entry (TYPE_3__*,scalar_t__,unsigned int,long long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 

__attribute__((used)) static int pmp_header(AVFormatContext *s)
{
    PMPContext *pmp = s->priv_data;
    AVIOContext *pb = s->pb;
    int tb_num, tb_den;
    uint32_t index_cnt;
    int audio_codec_id = AV_CODEC_ID_NONE;
    int srate, channels;
    unsigned i;
    uint64_t pos;
    int64_t fsize = avio_size(pb);

    AVStream *vst = avformat_new_stream(s, NULL);
    if (!vst)
        return AVERROR(ENOMEM);
    vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    avio_skip(pb, 8);
    switch (avio_rl32(pb)) {
    case 0:
        vst->codecpar->codec_id = AV_CODEC_ID_MPEG4;
        break;
    case 1:
        vst->codecpar->codec_id = AV_CODEC_ID_H264;
        break;
    default:
        av_log(s, AV_LOG_ERROR, "Unsupported video format\n");
        break;
    }
    index_cnt          = avio_rl32(pb);
    vst->codecpar->width  = avio_rl32(pb);
    vst->codecpar->height = avio_rl32(pb);

    tb_num = avio_rl32(pb);
    tb_den = avio_rl32(pb);
    avpriv_set_pts_info(vst, 32, tb_num, tb_den);
    vst->nb_frames = index_cnt;
    vst->duration = index_cnt;

    switch (avio_rl32(pb)) {
    case 0:
        audio_codec_id = AV_CODEC_ID_MP3;
        break;
    case 1:
        av_log(s, AV_LOG_ERROR, "AAC not yet correctly supported\n");
        audio_codec_id = AV_CODEC_ID_AAC;
        break;
    default:
        av_log(s, AV_LOG_ERROR, "Unsupported audio format\n");
        break;
    }
    pmp->num_streams = avio_rl16(pb) + 1;
    avio_skip(pb, 10);
    srate = avio_rl32(pb);
    channels = avio_rl32(pb) + 1;
    pos = avio_tell(pb) + 4LL*index_cnt;
    for (i = 0; i < index_cnt; i++) {
        uint32_t size = avio_rl32(pb);
        int flags = size & 1 ? AVINDEX_KEYFRAME : 0;
        if (avio_feof(pb)) {
            av_log(s, AV_LOG_FATAL, "Encountered EOF while reading index.\n");
            return AVERROR_INVALIDDATA;
        }
        size >>= 1;
        if (size < 9 + 4*pmp->num_streams) {
            av_log(s, AV_LOG_ERROR, "Packet too small\n");
            return AVERROR_INVALIDDATA;
        }
        av_add_index_entry(vst, pos, i, size, 0, flags);
        pos += size;
        if (fsize > 0 && i == 0 && pos > fsize) {
            av_log(s, AV_LOG_ERROR, "File ends before first packet\n");
            return AVERROR_INVALIDDATA;
        }
    }
    for (i = 1; i < pmp->num_streams; i++) {
        AVStream *ast = avformat_new_stream(s, NULL);
        if (!ast)
            return AVERROR(ENOMEM);
        ast->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
        ast->codecpar->codec_id    = audio_codec_id;
        ast->codecpar->channels    = channels;
        ast->codecpar->sample_rate = srate;
        avpriv_set_pts_info(ast, 32, 1, srate);
    }
    return 0;
}