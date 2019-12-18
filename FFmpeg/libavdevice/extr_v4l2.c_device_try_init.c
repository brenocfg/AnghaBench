#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_7__ {scalar_t__ codec_id; int ff_fmt; int /*<<< orphan*/  v4l2_fmt; } ;
struct TYPE_6__ {scalar_t__ video_codec_id; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ av_x_if_null (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avcodec_get_name (scalar_t__) ; 
 int device_init (TYPE_1__*,int*,int*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ff_fmt_conversion_table ; 
 int /*<<< orphan*/  ff_fmt_ff2v4l (int,scalar_t__) ; 
 int ff_fmt_v4l2codec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_try_init(AVFormatContext *ctx,
                           enum AVPixelFormat pix_fmt,
                           int *width,
                           int *height,
                           uint32_t *desired_format,
                           enum AVCodecID *codec_id)
{
    int ret, i;

    *desired_format = ff_fmt_ff2v4l(pix_fmt, ctx->video_codec_id);

    if (*desired_format) {
        ret = device_init(ctx, width, height, *desired_format);
        if (ret < 0) {
            *desired_format = 0;
            if (ret != AVERROR(EINVAL))
                return ret;
        }
    }

    if (!*desired_format) {
        for (i = 0; ff_fmt_conversion_table[i].codec_id != AV_CODEC_ID_NONE; i++) {
            if (ctx->video_codec_id == AV_CODEC_ID_NONE ||
                ff_fmt_conversion_table[i].codec_id == ctx->video_codec_id) {
                av_log(ctx, AV_LOG_DEBUG, "Trying to set codec:%s pix_fmt:%s\n",
                       avcodec_get_name(ff_fmt_conversion_table[i].codec_id),
                       (char *)av_x_if_null(av_get_pix_fmt_name(ff_fmt_conversion_table[i].ff_fmt), "none"));

                *desired_format = ff_fmt_conversion_table[i].v4l2_fmt;
                ret = device_init(ctx, width, height, *desired_format);
                if (ret >= 0)
                    break;
                else if (ret != AVERROR(EINVAL))
                    return ret;
                *desired_format = 0;
            }
        }

        if (*desired_format == 0) {
            av_log(ctx, AV_LOG_ERROR, "Cannot find a proper format for "
                   "codec '%s' (id %d), pixel format '%s' (id %d)\n",
                   avcodec_get_name(ctx->video_codec_id), ctx->video_codec_id,
                   (char *)av_x_if_null(av_get_pix_fmt_name(pix_fmt), "none"), pix_fmt);
            ret = AVERROR(EINVAL);
        }
    }

    *codec_id = ff_fmt_v4l2codec(*desired_format);
    if (*codec_id == AV_CODEC_ID_NONE)
        av_assert0(ret == AVERROR(EINVAL));
    return ret;
}