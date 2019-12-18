#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_18__ {int yres; int xres; int xoffset; int yoffset; } ;
struct TYPE_17__ {int format; int width; int height; int bits_per_coded_sample; } ;
struct TYPE_16__ {TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_15__ {int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int line_length; } ;
struct TYPE_14__ {int xoffset; int yoffset; TYPE_2__ fixinfo; TYPE_7__ varinfo; int /*<<< orphan*/ * data; int /*<<< orphan*/  fd; } ;
struct TYPE_12__ {TYPE_6__* codecpar; } ;
typedef  TYPE_3__ FBDevContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FBIOGET_VSCREENINFO ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  errno ; 
 int ff_get_pixfmt_from_fb_varinfo (TYPE_7__*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fbdev_write_packet(AVFormatContext *h, AVPacket *pkt)
{
    FBDevContext *fbdev = h->priv_data;
    uint8_t *pin, *pout;
    enum AVPixelFormat fb_pix_fmt;
    int disp_height;
    int bytes_to_copy;
    AVCodecParameters *par = h->streams[0]->codecpar;
    enum AVPixelFormat video_pix_fmt = par->format;
    int video_width = par->width;
    int video_height = par->height;
    int bytes_per_pixel = ((par->bits_per_coded_sample + 7) >> 3);
    int src_line_size = video_width * bytes_per_pixel;
    int i;

    if (ioctl(fbdev->fd, FBIOGET_VSCREENINFO, &fbdev->varinfo) < 0)
        av_log(h, AV_LOG_WARNING,
               "Error refreshing variable info: %s\n", av_err2str(AVERROR(errno)));

    fb_pix_fmt = ff_get_pixfmt_from_fb_varinfo(&fbdev->varinfo);

    if (fb_pix_fmt != video_pix_fmt) {
        av_log(h, AV_LOG_ERROR, "Pixel format %s is not supported, use %s\n",
               av_get_pix_fmt_name(video_pix_fmt), av_get_pix_fmt_name(fb_pix_fmt));
        return AVERROR(EINVAL);
    }

    disp_height = FFMIN(fbdev->varinfo.yres, video_height);
    bytes_to_copy = FFMIN(fbdev->varinfo.xres, video_width) * bytes_per_pixel;

    pin  = pkt->data;
    pout = fbdev->data +
           bytes_per_pixel * fbdev->varinfo.xoffset +
           fbdev->varinfo.yoffset * fbdev->fixinfo.line_length;

    if (fbdev->xoffset) {
        if (fbdev->xoffset < 0) {
            if (-fbdev->xoffset >= video_width) //nothing to display
                return 0;
            bytes_to_copy += fbdev->xoffset * bytes_per_pixel;
            pin -= fbdev->xoffset * bytes_per_pixel;
        } else {
            int diff = (video_width + fbdev->xoffset) - fbdev->varinfo.xres;
            if (diff > 0) {
                if (diff >= video_width) //nothing to display
                    return 0;
                bytes_to_copy -= diff * bytes_per_pixel;
            }
            pout += bytes_per_pixel * fbdev->xoffset;
        }
    }

    if (fbdev->yoffset) {
        if (fbdev->yoffset < 0) {
            if (-fbdev->yoffset >= video_height) //nothing to display
                return 0;
            disp_height += fbdev->yoffset;
            pin -= fbdev->yoffset * src_line_size;
        } else {
            int diff = (video_height + fbdev->yoffset) - fbdev->varinfo.yres;
            if (diff > 0) {
                if (diff >= video_height) //nothing to display
                    return 0;
                disp_height -= diff;
            }
            pout += fbdev->yoffset * fbdev->fixinfo.line_length;
        }
    }

    for (i = 0; i < disp_height; i++) {
        memcpy(pout, pin, bytes_to_copy);
        pout += fbdev->fixinfo.line_length;
        pin  += src_line_size;
    }

    return 0;
}