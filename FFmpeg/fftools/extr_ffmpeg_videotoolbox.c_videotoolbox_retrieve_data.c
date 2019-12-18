#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {TYPE_3__* tmp_frame; } ;
typedef  TYPE_1__ VTContext ;
struct TYPE_16__ {int /*<<< orphan*/  codec_tag; TYPE_2__* opaque; } ;
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/  linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {TYPE_1__* hwaccel_ctx; } ;
typedef  int OSType ;
typedef  TYPE_2__ InputStream ;
typedef  scalar_t__ CVReturn ;
typedef  int /*<<< orphan*/  CVPixelBufferRef ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_BGRA ; 
 int /*<<< orphan*/  AV_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  AV_PIX_FMT_P010 ; 
 int /*<<< orphan*/  AV_PIX_FMT_UYVY422 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/ * CVPixelBufferGetBaseAddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CVPixelBufferGetBaseAddressOfPlane (int /*<<< orphan*/ ,int) ; 
 int CVPixelBufferGetBytesPerRow (int /*<<< orphan*/ ) ; 
 int CVPixelBufferGetBytesPerRowOfPlane (int /*<<< orphan*/ ,int) ; 
 int CVPixelBufferGetPixelFormatType (int /*<<< orphan*/ ) ; 
 int CVPixelBufferGetPlaneCount (int /*<<< orphan*/ ) ; 
 scalar_t__ CVPixelBufferIsPlanar (int /*<<< orphan*/ ) ; 
 scalar_t__ CVPixelBufferLockBaseAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVPixelBufferUnlockBaseAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_fourcc2str (int /*<<< orphan*/ ) ; 
 int av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int av_frame_get_buffer (TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_frame_move_ref (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  av_image_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kCVPixelBufferLock_ReadOnly ; 
#define  kCVPixelFormatType_32BGRA 134 
#define  kCVPixelFormatType_420YpCbCr10BiPlanarFullRange 133 
#define  kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange 132 
#define  kCVPixelFormatType_420YpCbCr8BiPlanarFullRange 131 
#define  kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange 130 
#define  kCVPixelFormatType_420YpCbCr8Planar 129 
#define  kCVPixelFormatType_422YpCbCr8 128 
 scalar_t__ kCVReturnSuccess ; 
 int /*<<< orphan*/  videotoolbox_pixfmt ; 

__attribute__((used)) static int videotoolbox_retrieve_data(AVCodecContext *s, AVFrame *frame)
{
    InputStream *ist = s->opaque;
    VTContext  *vt = ist->hwaccel_ctx;
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)frame->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint8_t *data[4] = { 0 };
    int linesize[4] = { 0 };
    int planes, ret, i;

    av_frame_unref(vt->tmp_frame);

    switch (pixel_format) {
    case kCVPixelFormatType_420YpCbCr8Planar: vt->tmp_frame->format = AV_PIX_FMT_YUV420P; break;
    case kCVPixelFormatType_422YpCbCr8:       vt->tmp_frame->format = AV_PIX_FMT_UYVY422; break;
    case kCVPixelFormatType_32BGRA:           vt->tmp_frame->format = AV_PIX_FMT_BGRA; break;
#ifdef kCFCoreFoundationVersionNumber10_7
    case kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange:
    case kCVPixelFormatType_420YpCbCr8BiPlanarFullRange: vt->tmp_frame->format = AV_PIX_FMT_NV12; break;
#endif
#if HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    case kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange:
    case kCVPixelFormatType_420YpCbCr10BiPlanarFullRange: vt->tmp_frame->format = AV_PIX_FMT_P010; break;
#endif
    default:
        av_log(NULL, AV_LOG_ERROR,
               "%s: Unsupported pixel format: %s\n",
               av_fourcc2str(s->codec_tag), videotoolbox_pixfmt);
        return AVERROR(ENOSYS);
    }

    vt->tmp_frame->width  = frame->width;
    vt->tmp_frame->height = frame->height;
    ret = av_frame_get_buffer(vt->tmp_frame, 32);
    if (ret < 0)
        return ret;

    err = CVPixelBufferLockBaseAddress(pixbuf, kCVPixelBufferLock_ReadOnly);
    if (err != kCVReturnSuccess) {
        av_log(NULL, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        return AVERROR_UNKNOWN;
    }

    if (CVPixelBufferIsPlanar(pixbuf)) {

        planes = CVPixelBufferGetPlaneCount(pixbuf);
        for (i = 0; i < planes; i++) {
            data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } else {
        data[0] = CVPixelBufferGetBaseAddress(pixbuf);
        linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    av_image_copy(vt->tmp_frame->data, vt->tmp_frame->linesize,
                  (const uint8_t **)data, linesize, vt->tmp_frame->format,
                  frame->width, frame->height);

    ret = av_frame_copy_props(vt->tmp_frame, frame);
    CVPixelBufferUnlockBaseAddress(pixbuf, kCVPixelBufferLock_ReadOnly);
    if (ret < 0)
        return ret;

    av_frame_unref(frame);
    av_frame_move_ref(frame, vt->tmp_frame);

    return 0;
}