#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int warned_color_range; } ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_10__ {size_t width; size_t height; TYPE_1__* priv_data; } ;
struct TYPE_9__ {int format; int color_range; size_t* linesize; scalar_t__* data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVCOL_RANGE_NB ; 
 int AVCOL_RANGE_UNSPECIFIED ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  AV_PIX_FMT_NV12 130 
#define  AV_PIX_FMT_P010LE 129 
#define  AV_PIX_FMT_YUV420P 128 
 int /*<<< orphan*/  EINVAL ; 
 char* av_color_range_name (int) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int get_cv_pixel_format (TYPE_3__*,int,int,int*,int*) ; 

__attribute__((used)) static int get_cv_pixel_info(
    AVCodecContext *avctx,
    const AVFrame  *frame,
    int            *color,
    int            *plane_count,
    size_t         *widths,
    size_t         *heights,
    size_t         *strides,
    size_t         *contiguous_buf_size)
{
    VTEncContext *vtctx = avctx->priv_data;
    int av_format       = frame->format;
    int av_color_range  = frame->color_range;
    int i;
    int range_guessed;
    int status;

    status = get_cv_pixel_format(avctx, av_format, av_color_range, color, &range_guessed);
    if (status) {
        av_log(avctx,
            AV_LOG_ERROR,
            "Could not get pixel format for color format '%s' range '%s'.\n",
            av_get_pix_fmt_name(av_format),
            av_color_range > AVCOL_RANGE_UNSPECIFIED &&
            av_color_range < AVCOL_RANGE_NB ?
               av_color_range_name(av_color_range) :
               "Unknown");

        return AVERROR(EINVAL);
    }

    if (range_guessed) {
        if (!vtctx->warned_color_range) {
            vtctx->warned_color_range = true;
            av_log(avctx,
                   AV_LOG_WARNING,
                   "Color range not set for %s. Using MPEG range.\n",
                   av_get_pix_fmt_name(av_format));
        }
    }

    switch (av_format) {
    case AV_PIX_FMT_NV12:
        *plane_count = 2;

        widths [0] = avctx->width;
        heights[0] = avctx->height;
        strides[0] = frame ? frame->linesize[0] : avctx->width;

        widths [1] = (avctx->width  + 1) / 2;
        heights[1] = (avctx->height + 1) / 2;
        strides[1] = frame ? frame->linesize[1] : (avctx->width + 1) & -2;
        break;

    case AV_PIX_FMT_YUV420P:
        *plane_count = 3;

        widths [0] = avctx->width;
        heights[0] = avctx->height;
        strides[0] = frame ? frame->linesize[0] : avctx->width;

        widths [1] = (avctx->width  + 1) / 2;
        heights[1] = (avctx->height + 1) / 2;
        strides[1] = frame ? frame->linesize[1] : (avctx->width + 1) / 2;

        widths [2] = (avctx->width  + 1) / 2;
        heights[2] = (avctx->height + 1) / 2;
        strides[2] = frame ? frame->linesize[2] : (avctx->width + 1) / 2;
        break;

    case AV_PIX_FMT_P010LE:
        *plane_count = 2;
        widths[0] = avctx->width;
        heights[0] = avctx->height;
        strides[0] = frame ? frame->linesize[0] : (avctx->width * 2 + 63) & -64;

        widths[1] = (avctx->width + 1) / 2;
        heights[1] = (avctx->height + 1) / 2;
        strides[1] = frame ? frame->linesize[1] : ((avctx->width + 1) / 2 + 63) & -64;
        break;

    default:
        av_log(
               avctx,
               AV_LOG_ERROR,
               "Could not get frame format info for color %d range %d.\n",
               av_format,
               av_color_range);

        return AVERROR(EINVAL);
    }

    *contiguous_buf_size = 0;
    for (i = 0; i < *plane_count; i++) {
        if (i < *plane_count - 1 &&
            frame->data[i] + strides[i] * heights[i] != frame->data[i + 1]) {
            *contiguous_buf_size = 0;
            break;
        }

        *contiguous_buf_size += strides[i] * heights[i];
    }

    return 0;
}