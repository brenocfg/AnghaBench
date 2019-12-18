#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {unsigned int id; void* height; void* width; } ;
struct TYPE_14__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_13__ {TYPE_1__* codecpar; scalar_t__ start_time; void* nb_frames; void* duration; } ;
struct TYPE_12__ {unsigned int audio_size; int is_audio; int* pal; int is_first_video; } ;
struct TYPE_11__ {unsigned int sample_rate; int channels; void* height; void* width; scalar_t__ codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ GDVContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_GDV ; 
 int /*<<< orphan*/  AV_CODEC_ID_GREMLIN_DPCM ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16LE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_U8 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (TYPE_9__*) ; 
 TYPE_9__* FixedSize ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ ) ; 
 unsigned int avio_r8 (int /*<<< orphan*/ *) ; 
 void* avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,unsigned int) ; 

__attribute__((used)) static int gdv_read_header(AVFormatContext *ctx)
{
    GDVContext *gdv = ctx->priv_data;
    AVIOContext *pb = ctx->pb;
    AVStream *vst, *ast;
    unsigned fps, snd_flags, vid_depth, size_id;

    avio_skip(pb, 4);
    size_id = avio_rl16(pb);

    vst = avformat_new_stream(ctx, 0);
    if (!vst)
        return AVERROR(ENOMEM);

    vst->start_time        = 0;
    vst->duration          =
    vst->nb_frames         = avio_rl16(pb);

    fps = avio_rl16(pb);
    if (!fps)
        return AVERROR_INVALIDDATA;

    snd_flags = avio_rl16(pb);
    if (snd_flags & 1) {
        ast = avformat_new_stream(ctx, 0);
        if (!ast)
            return AVERROR(ENOMEM);

        ast->start_time = 0;
        ast->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
        ast->codecpar->codec_tag   = 0;
        ast->codecpar->sample_rate = avio_rl16(pb);
        ast->codecpar->channels    = 1 + !!(snd_flags & 2);
        if (snd_flags & 8) {
            ast->codecpar->codec_id = AV_CODEC_ID_GREMLIN_DPCM;
        } else {
            ast->codecpar->codec_id = (snd_flags & 4) ? AV_CODEC_ID_PCM_S16LE : AV_CODEC_ID_PCM_U8;
        }

        avpriv_set_pts_info(ast, 64, 1, ast->codecpar->sample_rate);
        gdv->audio_size = (ast->codecpar->sample_rate / fps) *
                           ast->codecpar->channels * (1 + !!(snd_flags & 4)) / (1 + !!(snd_flags & 8));
        gdv->is_audio = 1;
    } else {
        avio_skip(pb, 2);
    }
    vid_depth = avio_rl16(pb);
    avio_skip(pb, 4);

    vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    vst->codecpar->codec_id   = AV_CODEC_ID_GDV;
    vst->codecpar->codec_tag  = 0;
    vst->codecpar->width      = avio_rl16(pb);
    vst->codecpar->height     = avio_rl16(pb);

    if (vst->codecpar->width == 0 || vst->codecpar->height == 0) {
        int i;

        for (i = 0; i < FF_ARRAY_ELEMS(FixedSize) - 1; i++) {
            if (FixedSize[i].id == size_id)
                break;
        }

        vst->codecpar->width  = FixedSize[i].width;
        vst->codecpar->height = FixedSize[i].height;
    }

    avpriv_set_pts_info(vst, 64, 1, fps);

    if (vid_depth & 1) {
        int i;

        for (i = 0; i < 256; i++) {
            unsigned r = avio_r8(pb);
            unsigned g = avio_r8(pb);
            unsigned b = avio_r8(pb);
            gdv->pal[i] = 0xFFU << 24 | r << 18 | g << 10 | b << 2;
        }
    }

    gdv->is_first_video = 1;

    return 0;
}