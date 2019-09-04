#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int nb_streams; TYPE_2__** streams; } ;
struct TYPE_18__ {int width; int height; int /*<<< orphan*/  format; } ;
struct TYPE_16__ {int w; int h; void* end_pts; void* last_pts; int /*<<< orphan*/  frame; } ;
struct TYPE_17__ {size_t file_index; TYPE_4__ sub2video; TYPE_3__* dec_ctx; } ;
struct TYPE_15__ {int width; int height; } ;
struct TYPE_14__ {TYPE_1__* codecpar; } ;
struct TYPE_13__ {scalar_t__ codec_type; int width; int height; } ;
struct TYPE_12__ {TYPE_7__* ctx; } ;
typedef  TYPE_5__ InputStream ;
typedef  TYPE_6__ InputFilter ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_PIX_FMT_RGB32 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 void* INT64_MIN ; 
 int /*<<< orphan*/  av_frame_alloc () ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_10__** input_files ; 

__attribute__((used)) static int sub2video_prepare(InputStream *ist, InputFilter *ifilter)
{
    AVFormatContext *avf = input_files[ist->file_index]->ctx;
    int i, w, h;

    /* Compute the size of the canvas for the subtitles stream.
       If the subtitles codecpar has set a size, use it. Otherwise use the
       maximum dimensions of the video streams in the same file. */
    w = ifilter->width;
    h = ifilter->height;
    if (!(w && h)) {
        for (i = 0; i < avf->nb_streams; i++) {
            if (avf->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                w = FFMAX(w, avf->streams[i]->codecpar->width);
                h = FFMAX(h, avf->streams[i]->codecpar->height);
            }
        }
        if (!(w && h)) {
            w = FFMAX(w, 720);
            h = FFMAX(h, 576);
        }
        av_log(avf, AV_LOG_INFO, "sub2video: using %dx%d canvas\n", w, h);
    }
    ist->sub2video.w = ifilter->width  = w;
    ist->sub2video.h = ifilter->height = h;

    ifilter->width  = ist->dec_ctx->width  ? ist->dec_ctx->width  : ist->sub2video.w;
    ifilter->height = ist->dec_ctx->height ? ist->dec_ctx->height : ist->sub2video.h;

    /* rectangles are AV_PIX_FMT_PAL8, but we have no guarantee that the
       palettes for all rectangles are identical or compatible */
    ifilter->format = AV_PIX_FMT_RGB32;

    ist->sub2video.frame = av_frame_alloc();
    if (!ist->sub2video.frame)
        return AVERROR(ENOMEM);
    ist->sub2video.last_pts = INT64_MIN;
    ist->sub2video.end_pts  = INT64_MIN;
    return 0;
}