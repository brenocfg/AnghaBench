#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_10__ {int format; int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {scalar_t__ width; scalar_t__ height; } ;
typedef  int /*<<< orphan*/  OSType ;
typedef  scalar_t__ CVReturn ;
typedef  int /*<<< orphan*/  CVPixelBufferRef ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int AV_HWFRAME_MAP_READ ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CVPixelBufferGetBaseAddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVPixelBufferGetBaseAddressOfPlane (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CVPixelBufferGetBytesPerRow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVPixelBufferGetBytesPerRowOfPlane (int /*<<< orphan*/ ,int) ; 
 scalar_t__ CVPixelBufferGetHeight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVPixelBufferGetPixelFormatType (int /*<<< orphan*/ ) ; 
 int CVPixelBufferGetPlaneCount (int /*<<< orphan*/ ) ; 
 scalar_t__ CVPixelBufferGetWidth (int /*<<< orphan*/ ) ; 
 scalar_t__ CVPixelBufferIsPlanar (int /*<<< orphan*/ ) ; 
 scalar_t__ CVPixelBufferLockBaseAddress (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CVPixelBufferUnlockBaseAddress (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  av_fourcc2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_map_videotoolbox_format_to_pixfmt (int /*<<< orphan*/ ) ; 
 int ff_hwframe_map_create (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__ const*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ kCVPixelBufferLock_ReadOnly ; 
 scalar_t__ kCVReturnSuccess ; 
 int /*<<< orphan*/  vt_unmap ; 

__attribute__((used)) static int vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, const AVFrame *src,
                        int flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    int ret;
    int i;
    enum AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    if (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        return AVERROR_UNKNOWN;
    }

    if (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        return AVERROR_UNKNOWN;
    }

    if (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    if (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        return AVERROR_UNKNOWN;
    }

    if (CVPixelBufferIsPlanar(pixbuf)) {
        int planes = CVPixelBufferGetPlaneCount(pixbuf);
        for (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } else {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (void *)(uintptr_t)map_flags);
    if (ret < 0)
        goto unlock;

    return 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    return ret;
}