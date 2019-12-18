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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_13__ {int nb_frames; int duration; TYPE_1__* codecpar; scalar_t__ start_time; } ;
struct TYPE_12__ {int nb_frames; int buffer_size; int preload_count; int frame_blks; int start_offset; int max_video_blks; int max_audio_blks; int video_size; int audio_size; scalar_t__ current_frame_block; scalar_t__ current_frame; scalar_t__ got_audio; void* blocks_offset_table; void* frames_offset_table; void* blocks_count_table; void* temp_audio_frame; void* audio_frame; void* video_frame; } ;
struct TYPE_11__ {int channels; int sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; scalar_t__ codec_tag; int /*<<< orphan*/  codec_type; void* height; void* width; } ;
typedef  TYPE_2__ PAFDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PAF_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PAF_VIDEO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 void* av_mallocz (int) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  read_close (TYPE_4__*) ; 
 int /*<<< orphan*/  read_table (TYPE_4__*,void*,int) ; 

__attribute__((used)) static int read_header(AVFormatContext *s)
{
    PAFDemuxContext *p  = s->priv_data;
    AVIOContext     *pb = s->pb;
    AVStream        *ast, *vst;
    int ret = 0;

    avio_skip(pb, 132);

    vst = avformat_new_stream(s, 0);
    if (!vst)
        return AVERROR(ENOMEM);

    vst->start_time = 0;
    vst->nb_frames  =
    vst->duration   =
    p->nb_frames    = avio_rl32(pb);
    avio_skip(pb, 4);

    vst->codecpar->width  = avio_rl32(pb);
    vst->codecpar->height = avio_rl32(pb);
    avio_skip(pb, 4);

    vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    vst->codecpar->codec_tag  = 0;
    vst->codecpar->codec_id   = AV_CODEC_ID_PAF_VIDEO;
    avpriv_set_pts_info(vst, 64, 1, 10);

    ast = avformat_new_stream(s, 0);
    if (!ast)
        return AVERROR(ENOMEM);

    ast->start_time            = 0;
    ast->codecpar->codec_type     = AVMEDIA_TYPE_AUDIO;
    ast->codecpar->codec_tag      = 0;
    ast->codecpar->codec_id       = AV_CODEC_ID_PAF_AUDIO;
    ast->codecpar->channels       = 2;
    ast->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
    ast->codecpar->sample_rate    = 22050;
    avpriv_set_pts_info(ast, 64, 1, 22050);

    p->buffer_size    = avio_rl32(pb);
    p->preload_count  = avio_rl32(pb);
    p->frame_blks     = avio_rl32(pb);
    p->start_offset   = avio_rl32(pb);
    p->max_video_blks = avio_rl32(pb);
    p->max_audio_blks = avio_rl32(pb);
    if (p->buffer_size    < 175  ||
        p->max_audio_blks < 2    ||
        p->max_video_blks < 1    ||
        p->frame_blks     < 1    ||
        p->nb_frames      < 1    ||
        p->preload_count  < 1    ||
        p->buffer_size    > 2048 ||
        p->max_video_blks > 2048 ||
        p->max_audio_blks > 2048 ||
        p->nb_frames      > INT_MAX / sizeof(uint32_t) ||
        p->frame_blks     > INT_MAX / sizeof(uint32_t))
        return AVERROR_INVALIDDATA;

    p->blocks_count_table  = av_mallocz(p->nb_frames *
                                        sizeof(*p->blocks_count_table));
    p->frames_offset_table = av_mallocz(p->nb_frames *
                                        sizeof(*p->frames_offset_table));
    p->blocks_offset_table = av_mallocz(p->frame_blks *
                                        sizeof(*p->blocks_offset_table));

    p->video_size  = p->max_video_blks * p->buffer_size;
    p->video_frame = av_mallocz(p->video_size);

    p->audio_size       = p->max_audio_blks * p->buffer_size;
    p->audio_frame      = av_mallocz(p->audio_size);
    p->temp_audio_frame = av_mallocz(p->audio_size);

    if (!p->blocks_count_table  ||
        !p->frames_offset_table ||
        !p->blocks_offset_table ||
        !p->video_frame         ||
        !p->audio_frame         ||
        !p->temp_audio_frame) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    avio_seek(pb, p->buffer_size, SEEK_SET);

    read_table(s, p->blocks_count_table,  p->nb_frames);
    read_table(s, p->frames_offset_table, p->nb_frames);
    read_table(s, p->blocks_offset_table, p->frame_blks);

    p->got_audio = 0;
    p->current_frame = 0;
    p->current_frame_block = 0;

    avio_seek(pb, p->start_offset, SEEK_SET);

    return 0;

fail:
    read_close(s);

    return ret;
}