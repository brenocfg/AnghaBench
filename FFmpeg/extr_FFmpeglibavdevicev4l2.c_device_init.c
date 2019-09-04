#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct video_data {int interlaced; int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {int width; int height; scalar_t__ field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {struct video_data* priv_data; } ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  VIDIOC_S_FMT ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_format*) ; 

__attribute__((used)) static int device_init(AVFormatContext *ctx, int *width, int *height,
                       uint32_t pixelformat)
{
    struct video_data *s = ctx->priv_data;
    struct v4l2_format fmt = { .type = V4L2_BUF_TYPE_VIDEO_CAPTURE };
    int res = 0;

    fmt.fmt.pix.width = *width;
    fmt.fmt.pix.height = *height;
    fmt.fmt.pix.pixelformat = pixelformat;
    fmt.fmt.pix.field = V4L2_FIELD_ANY;

    /* Some drivers will fail and return EINVAL when the pixelformat
       is not supported (even if type field is valid and supported) */
    if (v4l2_ioctl(s->fd, VIDIOC_S_FMT, &fmt) < 0)
        res = AVERROR(errno);

    if ((*width != fmt.fmt.pix.width) || (*height != fmt.fmt.pix.height)) {
        av_log(ctx, AV_LOG_INFO,
               "The V4L2 driver changed the video from %dx%d to %dx%d\n",
               *width, *height, fmt.fmt.pix.width, fmt.fmt.pix.height);
        *width = fmt.fmt.pix.width;
        *height = fmt.fmt.pix.height;
    }

    if (pixelformat != fmt.fmt.pix.pixelformat) {
        av_log(ctx, AV_LOG_DEBUG,
               "The V4L2 driver changed the pixel format "
               "from 0x%08X to 0x%08X\n",
               pixelformat, fmt.fmt.pix.pixelformat);
        res = AVERROR(EINVAL);
    }

    if (fmt.fmt.pix.field == V4L2_FIELD_INTERLACED) {
        av_log(ctx, AV_LOG_DEBUG,
               "The V4L2 driver is using the interlaced mode\n");
        s->interlaced = 1;
    }

    return res;
}