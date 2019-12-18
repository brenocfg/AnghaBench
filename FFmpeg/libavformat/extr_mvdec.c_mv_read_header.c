#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_21__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_20__ {int nb_frames; TYPE_1__* codecpar; int /*<<< orphan*/  time_base; int /*<<< orphan*/  avg_frame_rate; } ;
struct TYPE_19__ {int nb_audio_tracks; int acompression; int aformat; int nb_video_tracks; } ;
struct TYPE_18__ {int sample_rate; int channels; int bits_per_coded_sample; void* codec_type; void* codec_id; void* height; void* width; scalar_t__ codec_tag; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ MvContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AUDIO_FORMAT_SIGNED ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 void* AVMEDIA_TYPE_AUDIO ; 
 void* AVMEDIA_TYPE_VIDEO ; 
 void* AV_CODEC_ID_MVC1 ; 
 void* AV_CODEC_ID_NONE ; 
 void* AV_CODEC_ID_PCM_S16BE ; 
 void* AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_ARGB ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_add_index_entry (TYPE_3__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  parse_audio_var ; 
 int /*<<< orphan*/  parse_global_var ; 
 int /*<<< orphan*/  parse_video_var ; 
 int /*<<< orphan*/  read_index (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int read_table (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_channels (TYPE_4__*,TYPE_3__*,void*) ; 
 int /*<<< orphan*/  var_read_metadata (TYPE_4__*,char*,int) ; 

__attribute__((used)) static int mv_read_header(AVFormatContext *avctx)
{
    MvContext *mv = avctx->priv_data;
    AVIOContext *pb = avctx->pb;
    AVStream *ast = NULL, *vst = NULL; //initialization to suppress warning
    int version, i;
    int ret;

    avio_skip(pb, 4);

    version = avio_rb16(pb);
    if (version == 2) {
        uint64_t timestamp;
        int v;
        avio_skip(pb, 22);

        /* allocate audio track first to prevent unnecessary seeking
         * (audio packet always precede video packet for a given frame) */
        ast = avformat_new_stream(avctx, NULL);
        if (!ast)
            return AVERROR(ENOMEM);

        vst = avformat_new_stream(avctx, NULL);
        if (!vst)
            return AVERROR(ENOMEM);
        avpriv_set_pts_info(vst, 64, 1, 15);
        vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        vst->avg_frame_rate    = av_inv_q(vst->time_base);
        vst->nb_frames         = avio_rb32(pb);
        v = avio_rb32(pb);
        switch (v) {
        case 1:
            vst->codecpar->codec_id = AV_CODEC_ID_MVC1;
            break;
        case 2:
            vst->codecpar->format = AV_PIX_FMT_ARGB;
            vst->codecpar->codec_id = AV_CODEC_ID_RAWVIDEO;
            break;
        default:
            avpriv_request_sample(avctx, "Video compression %i", v);
            break;
        }
        vst->codecpar->codec_tag = 0;
        vst->codecpar->width     = avio_rb32(pb);
        vst->codecpar->height    = avio_rb32(pb);
        avio_skip(pb, 12);

        ast->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
        ast->nb_frames          = vst->nb_frames;
        ast->codecpar->sample_rate = avio_rb32(pb);
        if (ast->codecpar->sample_rate <= 0) {
            av_log(avctx, AV_LOG_ERROR, "Invalid sample rate %d\n", ast->codecpar->sample_rate);
            return AVERROR_INVALIDDATA;
        }
        avpriv_set_pts_info(ast, 33, 1, ast->codecpar->sample_rate);
        if (set_channels(avctx, ast, avio_rb32(pb)) < 0)
            return AVERROR_INVALIDDATA;

        v = avio_rb32(pb);
        if (v == AUDIO_FORMAT_SIGNED) {
            ast->codecpar->codec_id = AV_CODEC_ID_PCM_S16BE;
        } else {
            avpriv_request_sample(avctx, "Audio compression (format %i)", v);
        }

        avio_skip(pb, 12);
        var_read_metadata(avctx, "title", 0x80);
        var_read_metadata(avctx, "comment", 0x100);
        avio_skip(pb, 0x80);

        timestamp = 0;
        for (i = 0; i < vst->nb_frames; i++) {
            uint32_t pos   = avio_rb32(pb);
            uint32_t asize = avio_rb32(pb);
            uint32_t vsize = avio_rb32(pb);
            if (avio_feof(pb))
                return AVERROR_INVALIDDATA;
            avio_skip(pb, 8);
            av_add_index_entry(ast, pos, timestamp, asize, 0, AVINDEX_KEYFRAME);
            av_add_index_entry(vst, pos + asize, i, vsize, 0, AVINDEX_KEYFRAME);
            timestamp += asize / (ast->codecpar->channels * 2);
        }
    } else if (!version && avio_rb16(pb) == 3) {
        avio_skip(pb, 4);

        if ((ret = read_table(avctx, NULL, parse_global_var)) < 0)
            return ret;

        if (mv->nb_audio_tracks > 1) {
            avpriv_request_sample(avctx, "Multiple audio streams support");
            return AVERROR_PATCHWELCOME;
        } else if (mv->nb_audio_tracks) {
            ast = avformat_new_stream(avctx, NULL);
            if (!ast)
                return AVERROR(ENOMEM);
            ast->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
            if ((read_table(avctx, ast, parse_audio_var)) < 0)
                return ret;
            if (mv->acompression == 100 &&
                mv->aformat == AUDIO_FORMAT_SIGNED &&
                ast->codecpar->bits_per_coded_sample == 16) {
                ast->codecpar->codec_id = AV_CODEC_ID_PCM_S16BE;
            } else {
                avpriv_request_sample(avctx,
                                      "Audio compression %i (format %i, sr %i)",
                                      mv->acompression, mv->aformat,
                                      ast->codecpar->bits_per_coded_sample);
                ast->codecpar->codec_id = AV_CODEC_ID_NONE;
            }
            if (ast->codecpar->channels <= 0) {
                av_log(avctx, AV_LOG_ERROR, "No valid channel count found.\n");
                return AVERROR_INVALIDDATA;
            }
        }

        if (mv->nb_video_tracks > 1) {
            avpriv_request_sample(avctx, "Multiple video streams support");
            return AVERROR_PATCHWELCOME;
        } else if (mv->nb_video_tracks) {
            vst = avformat_new_stream(avctx, NULL);
            if (!vst)
                return AVERROR(ENOMEM);
            vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
            if ((ret = read_table(avctx, vst, parse_video_var))<0)
                return ret;
        }

        if (mv->nb_audio_tracks)
            read_index(pb, ast);

        if (mv->nb_video_tracks)
            read_index(pb, vst);
    } else {
        avpriv_request_sample(avctx, "Version %i", version);
        return AVERROR_PATCHWELCOME;
    }

    return 0;
}