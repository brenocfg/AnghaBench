#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_30__ {char* path; int img_number; char** tmp; char** target; int /*<<< orphan*/  is_pipe; scalar_t__ muxer; scalar_t__ split_planes; scalar_t__ use_rename; scalar_t__ frame_pts; scalar_t__ use_strftime; scalar_t__ update; } ;
typedef  TYPE_3__ VideoMuxData ;
struct TYPE_35__ {int width; int height; int /*<<< orphan*/  format; } ;
struct TYPE_34__ {scalar_t__ (* io_open ) (TYPE_7__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__** streams; int /*<<< orphan*/ * pb; int /*<<< orphan*/  url; TYPE_3__* priv_data; } ;
struct TYPE_33__ {size_t stream_index; int pts; int size; scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_32__ {int nb_components; TYPE_2__* comp; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_31__ {size_t id; int /*<<< orphan*/  codecpar; } ;
struct TYPE_29__ {int depth; } ;
struct TYPE_28__ {TYPE_8__* codecpar; } ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPixFmtDescriptor ;
typedef  TYPE_6__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_7__ AVFormatContext ;
typedef  TYPE_8__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_FRAME_FILENAME_FLAGS_MULTIPLE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ av_get_frame_filename2 (char*,int,char*,int,int /*<<< orphan*/ ) ; 
 int av_interleaved_write_frame (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_packet_ref (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_6__*) ; 
 TYPE_5__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int av_write_trailer (TYPE_7__*) ; 
 int avcodec_parameters_copy (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int avformat_alloc_output_context2 (TYPE_7__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_7__*) ; 
 TYPE_4__* avformat_new_stream (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int avformat_write_header (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_7__*,int /*<<< orphan*/ **) ; 
 int ff_rename (char*,char*,TYPE_7__*) ; 
 struct tm* localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int strlen (char*) ; 
 scalar_t__ stub1 (TYPE_7__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_packet(AVFormatContext *s, AVPacket *pkt)
{
    VideoMuxData *img = s->priv_data;
    AVIOContext *pb[4];
    char filename[1024];
    AVCodecParameters *par = s->streams[pkt->stream_index]->codecpar;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(par->format);
    int i;
    int nb_renames = 0;

    if (!img->is_pipe) {
        if (img->update) {
            av_strlcpy(filename, img->path, sizeof(filename));
        } else if (img->use_strftime) {
            time_t now0;
            struct tm *tm, tmpbuf;
            time(&now0);
            tm = localtime_r(&now0, &tmpbuf);
            if (!strftime(filename, sizeof(filename), img->path, tm)) {
                av_log(s, AV_LOG_ERROR, "Could not get frame filename with strftime\n");
                return AVERROR(EINVAL);
            }
        } else if (img->frame_pts) {
            if (av_get_frame_filename2(filename, sizeof(filename), img->path, pkt->pts, AV_FRAME_FILENAME_FLAGS_MULTIPLE) < 0) {
                av_log(s, AV_LOG_ERROR, "Cannot write filename by pts of the frames.");
                return AVERROR(EINVAL);
            }
        } else if (av_get_frame_filename2(filename, sizeof(filename), img->path,
                                          img->img_number,
                                          AV_FRAME_FILENAME_FLAGS_MULTIPLE) < 0 &&
                   img->img_number > 1) {
            av_log(s, AV_LOG_ERROR,
                   "Could not get frame filename number %d from pattern '%s'. "
                   "Use '-frames:v 1' for a single image, or '-update' option, or use a pattern such as %%03d within the filename.\n",
                   img->img_number, img->path);
            return AVERROR(EINVAL);
        }
        for (i = 0; i < 4; i++) {
            snprintf(img->tmp[i], sizeof(img->tmp[i]), "%s.tmp", filename);
            av_strlcpy(img->target[i], filename, sizeof(img->target[i]));
            if (s->io_open(s, &pb[i], img->use_rename ? img->tmp[i] : filename, AVIO_FLAG_WRITE, NULL) < 0) {
                av_log(s, AV_LOG_ERROR, "Could not open file : %s\n", img->use_rename ? img->tmp[i] : filename);
                return AVERROR(EIO);
            }

            if (!img->split_planes || i+1 >= desc->nb_components)
                break;
            filename[strlen(filename) - 1] = "UVAx"[i];
        }
        if (img->use_rename)
            nb_renames = i + 1;
    } else {
        pb[0] = s->pb;
    }

    if (img->split_planes) {
        int ysize = par->width * par->height;
        int usize = AV_CEIL_RSHIFT(par->width, desc->log2_chroma_w) * AV_CEIL_RSHIFT(par->height, desc->log2_chroma_h);
        if (desc->comp[0].depth >= 9) {
            ysize *= 2;
            usize *= 2;
        }
        avio_write(pb[0], pkt->data                , ysize);
        avio_write(pb[1], pkt->data + ysize        , usize);
        avio_write(pb[2], pkt->data + ysize + usize, usize);
        ff_format_io_close(s, &pb[1]);
        ff_format_io_close(s, &pb[2]);
        if (desc->nb_components > 3) {
            avio_write(pb[3], pkt->data + ysize + 2*usize, ysize);
            ff_format_io_close(s, &pb[3]);
        }
    } else if (img->muxer) {
        int ret;
        AVStream *st;
        AVPacket pkt2 = {0};
        AVFormatContext *fmt = NULL;

        av_assert0(!img->split_planes);

        ret = avformat_alloc_output_context2(&fmt, NULL, img->muxer, s->url);
        if (ret < 0)
            return ret;
        st = avformat_new_stream(fmt, NULL);
        if (!st) {
            avformat_free_context(fmt);
            return AVERROR(ENOMEM);
        }
        st->id = pkt->stream_index;

        fmt->pb = pb[0];
        if ((ret = av_packet_ref(&pkt2, pkt))                             < 0 ||
            (ret = avcodec_parameters_copy(st->codecpar, s->streams[0]->codecpar)) < 0 ||
            (ret = avformat_write_header(fmt, NULL))                      < 0 ||
            (ret = av_interleaved_write_frame(fmt, &pkt2))                < 0 ||
            (ret = av_write_trailer(fmt))                                 < 0) {
            av_packet_unref(&pkt2);
            avformat_free_context(fmt);
            return ret;
        }
        av_packet_unref(&pkt2);
        avformat_free_context(fmt);
    } else {
        avio_write(pb[0], pkt->data, pkt->size);
    }
    avio_flush(pb[0]);
    if (!img->is_pipe) {
        ff_format_io_close(s, &pb[0]);
        for (i = 0; i < nb_renames; i++) {
            int ret = ff_rename(img->tmp[i], img->target[i], s);
            if (ret < 0)
                return ret;
        }
    }

    img->img_number++;
    return 0;
}