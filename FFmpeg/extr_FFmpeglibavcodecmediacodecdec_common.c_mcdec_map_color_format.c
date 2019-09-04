#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_6__ {int color_format; int pix_fmt; } ;
struct TYPE_5__ {int color_format; int /*<<< orphan*/  codec_name; scalar_t__ surface; } ;
typedef  TYPE_1__ MediaCodecDecContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_MEDIACODEC ; 
 int AV_PIX_FMT_NONE ; 
 int COLOR_FormatYCbYCr ; 
 int COLOR_TI_FormatYUV420PackedSemiPlanar ; 
 int FF_ARRAY_ELEMS (TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_3__* color_formats ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum AVPixelFormat mcdec_map_color_format(AVCodecContext *avctx,
                                                 MediaCodecDecContext *s,
                                                 int color_format)
{
    int i;
    enum AVPixelFormat ret = AV_PIX_FMT_NONE;

    if (s->surface) {
        return AV_PIX_FMT_MEDIACODEC;
    }

    if (!strcmp(s->codec_name, "OMX.k3.video.decoder.avc") && color_format == COLOR_FormatYCbYCr) {
        s->color_format = color_format = COLOR_TI_FormatYUV420PackedSemiPlanar;
    }

    for (i = 0; i < FF_ARRAY_ELEMS(color_formats); i++) {
        if (color_formats[i].color_format == color_format) {
            return color_formats[i].pix_fmt;
        }
    }

    av_log(avctx, AV_LOG_ERROR, "Output color format 0x%x (value=%d) is not supported\n",
        color_format, color_format);

    return ret;
}