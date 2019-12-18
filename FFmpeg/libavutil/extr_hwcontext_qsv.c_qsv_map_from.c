#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_24__ {int /*<<< orphan*/ * MemId; } ;
struct TYPE_25__ {TYPE_3__ Data; } ;
typedef  TYPE_4__ mfxFrameSurface1 ;
typedef  int /*<<< orphan*/  VASurfaceID ;
struct TYPE_29__ {scalar_t__ format; int /*<<< orphan*/ ** data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; void* hw_frames_ctx; TYPE_12__** buf; } ;
struct TYPE_28__ {scalar_t__ format; TYPE_2__* device_ctx; TYPE_1__* internal; } ;
struct TYPE_27__ {int flags; } ;
struct TYPE_26__ {TYPE_12__* child_frames_ref; } ;
struct TYPE_23__ {int type; } ;
struct TYPE_22__ {TYPE_5__* priv; } ;
struct TYPE_21__ {scalar_t__ data; } ;
typedef  TYPE_5__ QSVFramesContext ;
typedef  TYPE_6__ AVPixFmtDescriptor ;
typedef  TYPE_7__ AVHWFramesContext ;
typedef  TYPE_8__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_HWDEVICE_TYPE_DXVA2 129 
#define  AV_HWDEVICE_TYPE_VAAPI 128 
 int AV_PIX_FMT_FLAG_HWACCEL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 void* av_buffer_ref (TYPE_12__*) ; 
 TYPE_8__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_8__**) ; 
 int av_hwframe_map (TYPE_8__*,TYPE_8__*,int) ; 
 TYPE_6__* av_pix_fmt_desc_get (scalar_t__) ; 
 int ff_hwframe_map_create (TYPE_12__*,TYPE_8__*,TYPE_8__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, const AVFrame *src, int flags)
{
    QSVFramesContext *s = ctx->internal->priv;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    const AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    int ret = 0;

    if (!s->child_frames_ref)
        return AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    switch (child_frames_ctx->device_ctx->type) {
#if CONFIG_VAAPI
    case AV_HWDEVICE_TYPE_VAAPI:
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)surf->Data.MemId;
        break;
#endif
#if CONFIG_DXVA2
    case AV_HWDEVICE_TYPE_DXVA2:
        child_data = surf->Data.MemId;
        break;
#endif
    default:
        return AVERROR(ENOSYS);
    }

    if (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, NULL, NULL);
        if (ret < 0)
            return ret;

        dst->width   = src->width;
        dst->height  = src->height;
        dst->data[3] = child_data;

        return 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    if (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        return AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    if (!dummy)
        return AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    if (!dummy->buf[0] || !dummy->hw_frames_ctx)
        goto fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->data[3]       = child_data;

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    return ret;
}