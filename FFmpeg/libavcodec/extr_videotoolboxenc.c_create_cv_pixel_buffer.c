#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widths ;
typedef  int /*<<< orphan*/  strides ;
typedef  int /*<<< orphan*/  heights ;
struct TYPE_12__ {int /*<<< orphan*/ * session; } ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_14__ {scalar_t__ pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_13__ {scalar_t__ format; int /*<<< orphan*/  color_range; scalar_t__* data; } ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/ * CVPixelBufferRef ;
typedef  scalar_t__ CVPixelBufferPoolRef ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_NUM_DATA_POINTERS ; 
 scalar_t__ AV_PIX_FMT_VIDEOTOOLBOX ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRetain (int /*<<< orphan*/ *) ; 
 int CVPixelBufferPoolCreatePixelBuffer (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ VTCompressionSessionGetPixelBufferPool (int /*<<< orphan*/ *) ; 
 scalar_t__ VTCompressionSessionPrepareToEncodeFrames (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int copy_avframe_to_pixel_buffer (TYPE_3__*,TYPE_2__ const*,int /*<<< orphan*/ *,size_t*,size_t*) ; 
 int get_cv_pixel_info (TYPE_3__*,TYPE_2__ const*,int*,int*,size_t*,size_t*,size_t*,size_t*) ; 
 scalar_t__ kVTInvalidSessionErr ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int vtenc_configure_encoder (TYPE_3__*) ; 

__attribute__((used)) static int create_cv_pixel_buffer(AVCodecContext   *avctx,
                                  const AVFrame    *frame,
                                  CVPixelBufferRef *cv_img)
{
    int plane_count;
    int color;
    size_t widths [AV_NUM_DATA_POINTERS];
    size_t heights[AV_NUM_DATA_POINTERS];
    size_t strides[AV_NUM_DATA_POINTERS];
    int status;
    size_t contiguous_buf_size;
    CVPixelBufferPoolRef pix_buf_pool;
    VTEncContext* vtctx = avctx->priv_data;

    if (avctx->pix_fmt == AV_PIX_FMT_VIDEOTOOLBOX) {
        av_assert0(frame->format == AV_PIX_FMT_VIDEOTOOLBOX);

        *cv_img = (CVPixelBufferRef)frame->data[3];
        av_assert0(*cv_img);

        CFRetain(*cv_img);
        return 0;
    }

    memset(widths,  0, sizeof(widths));
    memset(heights, 0, sizeof(heights));
    memset(strides, 0, sizeof(strides));

    status = get_cv_pixel_info(
        avctx,
        frame,
        &color,
        &plane_count,
        widths,
        heights,
        strides,
        &contiguous_buf_size
    );

    if (status) {
        av_log(
            avctx,
            AV_LOG_ERROR,
            "Error: Cannot convert format %d color_range %d: %d\n",
            frame->format,
            frame->color_range,
            status
        );

        return AVERROR_EXTERNAL;
    }

    pix_buf_pool = VTCompressionSessionGetPixelBufferPool(vtctx->session);
    if (!pix_buf_pool) {
        /* On iOS, the VT session is invalidated when the APP switches from
         * foreground to background and vice versa. Fetch the actual error code
         * of the VT session to detect that case and restart the VT session
         * accordingly. */
        OSStatus vtstatus;

        vtstatus = VTCompressionSessionPrepareToEncodeFrames(vtctx->session);
        if (vtstatus == kVTInvalidSessionErr) {
            CFRelease(vtctx->session);
            vtctx->session = NULL;
            status = vtenc_configure_encoder(avctx);
            if (status == 0)
                pix_buf_pool = VTCompressionSessionGetPixelBufferPool(vtctx->session);
        }
        if (!pix_buf_pool) {
            av_log(avctx, AV_LOG_ERROR, "Could not get pixel buffer pool.\n");
            return AVERROR_EXTERNAL;
        }
        else
            av_log(avctx, AV_LOG_WARNING, "VT session restarted because of a "
                   "kVTInvalidSessionErr error.\n");
    }

    status = CVPixelBufferPoolCreatePixelBuffer(NULL,
                                                pix_buf_pool,
                                                cv_img);


    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Could not create pixel buffer from pool: %d.\n", status);
        return AVERROR_EXTERNAL;
    }

    status = copy_avframe_to_pixel_buffer(avctx, frame, *cv_img, strides, heights);
    if (status) {
        CFRelease(*cv_img);
        *cv_img = NULL;
        return status;
    }

    return 0;
}