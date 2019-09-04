#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fmtdesc {int /*<<< orphan*/  index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  fdesc ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_6__ {int av_pix_fmt; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ V4L2Context ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CODEC_ID_RAWVIDEO ; 
 int AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  VIDIOC_ENUM_FMT ; 
 TYPE_4__* ctx_to_m2mctx (TYPE_1__*) ; 
 int ff_v4l2_format_v4l2_to_avfmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_fmtdesc*) ; 
 int /*<<< orphan*/  memset (struct v4l2_fmtdesc*,int /*<<< orphan*/ ,int) ; 
 int v4l2_try_raw_format (TYPE_1__*,int) ; 

__attribute__((used)) static int v4l2_get_raw_format(V4L2Context* ctx, enum AVPixelFormat *p)
{
    enum AVPixelFormat pixfmt = ctx->av_pix_fmt;
    struct v4l2_fmtdesc fdesc;
    int ret;

    memset(&fdesc, 0, sizeof(fdesc));
    fdesc.type = ctx->type;

    if (pixfmt != AV_PIX_FMT_NONE) {
        ret = v4l2_try_raw_format(ctx, pixfmt);
        if (!ret)
            return 0;
    }

    for (;;) {
        ret = ioctl(ctx_to_m2mctx(ctx)->fd, VIDIOC_ENUM_FMT, &fdesc);
        if (ret)
            return AVERROR(EINVAL);

        pixfmt = ff_v4l2_format_v4l2_to_avfmt(fdesc.pixelformat, AV_CODEC_ID_RAWVIDEO);
        ret = v4l2_try_raw_format(ctx, pixfmt);
        if (ret){
            fdesc.index++;
            continue;
        }

        *p = pixfmt;

        return 0;
    }

    return AVERROR(EINVAL);
}