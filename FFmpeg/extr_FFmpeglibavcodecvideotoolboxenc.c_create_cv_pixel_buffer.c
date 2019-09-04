#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widths ;
typedef  int /*<<< orphan*/  strides ;
typedef  int /*<<< orphan*/  heights ;
struct TYPE_15__ {scalar_t__ pix_fmt; } ;
struct TYPE_14__ {scalar_t__ format; scalar_t__* data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  color_range; } ;
typedef  int CVPixelBufferRef ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_NUM_DATA_POINTERS ; 
 scalar_t__ AV_PIX_FMT_VIDEOTOOLBOX ; 
 int /*<<< orphan*/  CFDictionaryCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRetain (int) ; 
 int /*<<< orphan*/  CVBufferSetAttachments (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CVPixelBufferCreateWithPlanarBytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t,int,void**,size_t*,size_t*,size_t*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  add_color_attr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_1__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int av_frame_ref (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free_avframe ; 
 int get_cv_pixel_info (TYPE_2__*,TYPE_1__ const*,int*,int*,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFCopyStringDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 
 int /*<<< orphan*/  kCVAttachmentMode_ShouldPropagate ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

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
#if TARGET_OS_IPHONE
    CVPixelBufferPoolRef pix_buf_pool;
    VTEncContext* vtctx = avctx->priv_data;
#else
    CFMutableDictionaryRef pix_buf_attachments = CFDictionaryCreateMutable(
                                                   kCFAllocatorDefault,
                                                   10,
                                                   &kCFCopyStringDictionaryKeyCallBacks,
                                                   &kCFTypeDictionaryValueCallBacks);

    if (!pix_buf_attachments) return AVERROR(ENOMEM);
#endif

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

#if TARGET_OS_IPHONE
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
#else
    AVFrame *enc_frame = av_frame_alloc();
    if (!enc_frame) return AVERROR(ENOMEM);

    status = av_frame_ref(enc_frame, frame);
    if (status) {
        av_frame_free(&enc_frame);
        return status;
    }

    status = CVPixelBufferCreateWithPlanarBytes(
        kCFAllocatorDefault,
        enc_frame->width,
        enc_frame->height,
        color,
        NULL,
        contiguous_buf_size,
        plane_count,
        (void **)enc_frame->data,
        widths,
        heights,
        strides,
        free_avframe,
        enc_frame,
        NULL,
        cv_img
    );

    add_color_attr(avctx, pix_buf_attachments);
    CVBufferSetAttachments(*cv_img, pix_buf_attachments, kCVAttachmentMode_ShouldPropagate);
    CFRelease(pix_buf_attachments);

    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Error: Could not create CVPixelBuffer: %d\n", status);
        return AVERROR_EXTERNAL;
    }
#endif

    return 0;
}