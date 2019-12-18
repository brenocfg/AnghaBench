#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct video_data {int /*<<< orphan*/  fd; } ;
struct v4l2_fmtdesc {int flags; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_8__ {char* name; } ;
struct TYPE_7__ {struct video_data* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVCodecDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_FMT_FLAG_COMPRESSED ; 
 int V4L2_FMT_FLAG_EMULATED ; 
 int V4L_COMPFORMATS ; 
 int V4L_RAWFORMATS ; 
 int /*<<< orphan*/  VIDIOC_ENUM_FMT ; 
 char* av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* avcodec_descriptor_get (int) ; 
 int ff_fmt_v4l2codec (int /*<<< orphan*/ ) ; 
 int ff_fmt_v4l2ff (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_framesizes (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_fmtdesc*) ; 

__attribute__((used)) static void list_formats(AVFormatContext *ctx, int type)
{
    const struct video_data *s = ctx->priv_data;
    struct v4l2_fmtdesc vfd = { .type = V4L2_BUF_TYPE_VIDEO_CAPTURE };

    while(!v4l2_ioctl(s->fd, VIDIOC_ENUM_FMT, &vfd)) {
        enum AVCodecID codec_id = ff_fmt_v4l2codec(vfd.pixelformat);
        enum AVPixelFormat pix_fmt = ff_fmt_v4l2ff(vfd.pixelformat, codec_id);

        vfd.index++;

        if (!(vfd.flags & V4L2_FMT_FLAG_COMPRESSED) &&
            type & V4L_RAWFORMATS) {
            const char *fmt_name = av_get_pix_fmt_name(pix_fmt);
            av_log(ctx, AV_LOG_INFO, "Raw       : %11s : %20s :",
                   fmt_name ? fmt_name : "Unsupported",
                   vfd.description);
        } else if (vfd.flags & V4L2_FMT_FLAG_COMPRESSED &&
                   type & V4L_COMPFORMATS) {
            const AVCodecDescriptor *desc = avcodec_descriptor_get(codec_id);
            av_log(ctx, AV_LOG_INFO, "Compressed: %11s : %20s :",
                   desc ? desc->name : "Unsupported",
                   vfd.description);
        } else {
            continue;
        }

#ifdef V4L2_FMT_FLAG_EMULATED
        if (vfd.flags & V4L2_FMT_FLAG_EMULATED)
            av_log(ctx, AV_LOG_INFO, " Emulated :");
#endif
#if HAVE_STRUCT_V4L2_FRMIVALENUM_DISCRETE
        list_framesizes(ctx, vfd.pixelformat);
#endif
        av_log(ctx, AV_LOG_INFO, "\n");
    }
}