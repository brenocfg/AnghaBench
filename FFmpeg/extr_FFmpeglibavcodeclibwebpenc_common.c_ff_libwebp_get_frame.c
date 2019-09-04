#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_22__ {scalar_t__ width; scalar_t__ height; int use_argb; int argb_stride; int y_stride; int uv_stride; int a_stride; int /*<<< orphan*/ * memory_; int /*<<< orphan*/  error_code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/ * a; int /*<<< orphan*/ * v; int /*<<< orphan*/ * u; int /*<<< orphan*/ * y; int /*<<< orphan*/ * argb; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_25__ {scalar_t__ width; scalar_t__ height; scalar_t__ pix_fmt; } ;
struct TYPE_24__ {int** data; int* linesize; int width; int height; scalar_t__ format; } ;
struct TYPE_23__ {int conversion_warning; int cr_threshold; int chroma_warning; int cr_size; scalar_t__ lossless; TYPE_15__* ref; } ;
struct TYPE_21__ {int** data; } ;
typedef  TYPE_2__ LibWebPContextCommon ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_RGB32 ; 
 scalar_t__ AV_PIX_FMT_YUVA420P ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 scalar_t__ WEBP_MAX_DIMENSION ; 
 int /*<<< orphan*/  WEBP_YUV420 ; 
 int /*<<< orphan*/  WEBP_YUV420A ; 
 int /*<<< orphan*/  WebPCleanupTransparentArea (TYPE_1__*) ; 
 int WebPPictureInit (TYPE_1__*) ; 
 int WebPPictureYUVAToARGB (TYPE_1__*) ; 
 TYPE_3__* av_frame_alloc () ; 
 TYPE_15__* av_frame_clone (TYPE_3__ const*) ; 
 int /*<<< orphan*/  av_frame_copy (TYPE_3__*,TYPE_3__ const*) ; 
 int av_frame_get_buffer (TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* av_malloc (int) ; 
 int libwebp_error_to_averror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

int ff_libwebp_get_frame(AVCodecContext *avctx, LibWebPContextCommon *s,
                         const AVFrame *frame, AVFrame **alt_frame_ptr,
                         WebPPicture **pic_ptr) {
    int ret;
    WebPPicture *pic = NULL;
    AVFrame *alt_frame = NULL;

    if (avctx->width > WEBP_MAX_DIMENSION || avctx->height > WEBP_MAX_DIMENSION) {
        av_log(avctx, AV_LOG_ERROR, "Picture size is too large. Max is %dx%d.\n",
               WEBP_MAX_DIMENSION, WEBP_MAX_DIMENSION);
        return AVERROR(EINVAL);
    }

    *pic_ptr = av_malloc(sizeof(*pic));
    pic = *pic_ptr;
    if (!pic)
        return AVERROR(ENOMEM);

    ret = WebPPictureInit(pic);
    if (!ret) {
        ret = AVERROR_UNKNOWN;
        goto end;
    }
    pic->width  = avctx->width;
    pic->height = avctx->height;

    if (avctx->pix_fmt == AV_PIX_FMT_RGB32) {
        if (!s->lossless) {
            /* libwebp will automatically convert RGB input to YUV when
               encoding lossy. */
            if (!s->conversion_warning) {
                av_log(avctx, AV_LOG_WARNING,
                       "Using libwebp for RGB-to-YUV conversion. You may want "
                       "to consider passing in YUV instead for lossy "
                       "encoding.\n");
                s->conversion_warning = 1;
            }
        }
        pic->use_argb    = 1;
        pic->argb        = (uint32_t *)frame->data[0];
        pic->argb_stride = frame->linesize[0] / 4;
    } else {
        if (frame->linesize[1] != frame->linesize[2] || s->cr_threshold) {
            if (!s->chroma_warning && !s->cr_threshold) {
                av_log(avctx, AV_LOG_WARNING,
                       "Copying frame due to differing chroma linesizes.\n");
                s->chroma_warning = 1;
            }
            *alt_frame_ptr = av_frame_alloc();
            alt_frame = *alt_frame_ptr;
            if (!alt_frame) {
                ret = AVERROR(ENOMEM);
                goto end;
            }
            alt_frame->width  = frame->width;
            alt_frame->height = frame->height;
            alt_frame->format = frame->format;
            if (s->cr_threshold)
                alt_frame->format = AV_PIX_FMT_YUVA420P;
            ret = av_frame_get_buffer(alt_frame, 32);
            if (ret < 0)
                goto end;
            alt_frame->format = frame->format;
            av_frame_copy(alt_frame, frame);
            frame = alt_frame;
            if (s->cr_threshold) {
                int x,y, x2, y2, p;
                int bs = s->cr_size;

                if (!s->ref) {
                    s->ref = av_frame_clone(frame);
                    if (!s->ref) {
                        ret = AVERROR(ENOMEM);
                        goto end;
                    }
                }

                alt_frame->format = AV_PIX_FMT_YUVA420P;
                for (y = 0; y < frame->height; y+= bs) {
                    for (x = 0; x < frame->width; x+= bs) {
                        int skip;
                        int sse = 0;
                        for (p = 0; p < 3; p++) {
                            int bs2 = bs >> !!p;
                            int w = AV_CEIL_RSHIFT(frame->width , !!p);
                            int h = AV_CEIL_RSHIFT(frame->height, !!p);
                            int xs = x >> !!p;
                            int ys = y >> !!p;
                            for (y2 = ys; y2 < FFMIN(ys + bs2, h); y2++) {
                                for (x2 = xs; x2 < FFMIN(xs + bs2, w); x2++) {
                                    int diff =  frame->data[p][frame->linesize[p] * y2 + x2]
                                              -s->ref->data[p][frame->linesize[p] * y2 + x2];
                                    sse += diff*diff;
                                }
                            }
                        }
                        skip = sse < s->cr_threshold && frame->data[3] != s->ref->data[3];
                        if (!skip)
                            for (p = 0; p < 3; p++) {
                                int bs2 = bs >> !!p;
                                int w = AV_CEIL_RSHIFT(frame->width , !!p);
                                int h = AV_CEIL_RSHIFT(frame->height, !!p);
                                int xs = x >> !!p;
                                int ys = y >> !!p;
                                for (y2 = ys; y2 < FFMIN(ys + bs2, h); y2++) {
                                    memcpy(&s->ref->data[p][frame->linesize[p] * y2 + xs],
                                            & frame->data[p][frame->linesize[p] * y2 + xs], FFMIN(bs2, w-xs));
                                }
                            }
                        for (y2 = y; y2 < FFMIN(y+bs, frame->height); y2++) {
                            memset(&frame->data[3][frame->linesize[3] * y2 + x],
                                    skip ? 0 : 255,
                                    FFMIN(bs, frame->width-x));
                        }
                    }
                }
            }
        }

        pic->use_argb  = 0;
        pic->y         = frame->data[0];
        pic->u         = frame->data[1];
        pic->v         = frame->data[2];
        pic->y_stride  = frame->linesize[0];
        pic->uv_stride = frame->linesize[1];
        if (frame->format == AV_PIX_FMT_YUVA420P) {
            pic->colorspace = WEBP_YUV420A;
            pic->a          = frame->data[3];
            pic->a_stride   = frame->linesize[3];
            if (alt_frame)
                WebPCleanupTransparentArea(pic);
        } else {
            pic->colorspace = WEBP_YUV420;
        }

        if (s->lossless) {
            /* We do not have a way to automatically prioritize RGB over YUV
               in automatic pixel format conversion based on whether we're
               encoding lossless or lossy, so we do conversion with libwebp as
               a convenience. */
            if (!s->conversion_warning) {
                av_log(avctx, AV_LOG_WARNING,
                       "Using libwebp for YUV-to-RGB conversion. You may want "
                       "to consider passing in RGB instead for lossless "
                       "encoding.\n");
                s->conversion_warning = 1;
            }

#if (WEBP_ENCODER_ABI_VERSION <= 0x201)
            /* libwebp should do the conversion automatically, but there is a
               bug that causes it to return an error instead, so a work-around
               is required.
               See https://code.google.com/p/webp/issues/detail?id=178 */
            pic->memory_ = (void*)1;  /* something non-null */
            ret = WebPPictureYUVAToARGB(pic);
            if (!ret) {
                av_log(avctx, AV_LOG_ERROR,
                       "WebPPictureYUVAToARGB() failed with error: %d\n",
                       pic->error_code);
                ret = libwebp_error_to_averror(pic->error_code);
                goto end;
            }
            pic->memory_ = NULL;  /* restore pointer */
#endif
        }
    }
end:
    return ret;
}