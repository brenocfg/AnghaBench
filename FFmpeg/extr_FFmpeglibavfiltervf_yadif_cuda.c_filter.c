#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_6__* csp; TYPE_5__* cur; TYPE_4__* next; TYPE_3__* prev; } ;
typedef  TYPE_7__ YADIFContext ;
struct TYPE_28__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_27__ {int /*<<< orphan*/  cu_func_ushort2; int /*<<< orphan*/  cu_func_ushort; int /*<<< orphan*/  cu_func_uchar2; int /*<<< orphan*/  cu_func_uchar; int /*<<< orphan*/  cu_ctx; TYPE_2__* hwctx; TYPE_7__ yadif; } ;
struct TYPE_25__ {int nb_components; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  name; TYPE_12__* comp; } ;
struct TYPE_24__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__* data; } ;
struct TYPE_23__ {scalar_t__* data; } ;
struct TYPE_22__ {scalar_t__* data; } ;
struct TYPE_21__ {TYPE_1__* internal; } ;
struct TYPE_20__ {TYPE_9__* cuda_dl; } ;
struct TYPE_19__ {int plane; int depth; int shift; int step; } ;
struct TYPE_18__ {TYPE_8__* priv; } ;
struct TYPE_17__ {int* linesize; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__* data; } ;
typedef  TYPE_8__ DeintCUDAContext ;
typedef  TYPE_9__ CudaFunctions ;
typedef  int /*<<< orphan*/  CUfunction ;
typedef  int /*<<< orphan*/  CUdeviceptr ;
typedef  int /*<<< orphan*/  CUcontext ;
typedef  int /*<<< orphan*/  CUarray_format ;
typedef  TYPE_10__ AVFrame ;
typedef  TYPE_11__ AVFilterContext ;
typedef  TYPE_12__ AVComponentDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CU_AD_FORMAT_UNSIGNED_INT16 ; 
 int /*<<< orphan*/  CU_AD_FORMAT_UNSIGNED_INT8 ; 
 int /*<<< orphan*/  av_log (TYPE_11__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  call_kernel (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void filter(AVFilterContext *ctx, AVFrame *dst,
                   int parity, int tff)
{
    DeintCUDAContext *s = ctx->priv;
    YADIFContext *y = &s->yadif;
    CudaFunctions *cu = s->hwctx->internal->cuda_dl;
    CUcontext dummy;
    int i, ret;

    ret = CHECK_CU(cu->cuCtxPushCurrent(s->cu_ctx));
    if (ret < 0)
        return;

    for (i = 0; i < y->csp->nb_components; i++) {
        CUfunction func;
        CUarray_format format;
        int pixel_size, channels;
        const AVComponentDescriptor *comp = &y->csp->comp[i];

        if (comp->plane < i) {
            // We process planes as a whole, so don't reprocess
            // them for additional components
            continue;
        }

        pixel_size = (comp->depth + comp->shift) / 8;
        channels = comp->step / pixel_size;
        if (pixel_size > 2 || channels > 2) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n", y->csp->name);
            goto exit;
        }
        switch (pixel_size) {
        case 1:
            func = channels == 1 ? s->cu_func_uchar : s->cu_func_uchar2;
            format = CU_AD_FORMAT_UNSIGNED_INT8;
            break;
        case 2:
            func = channels == 1 ? s->cu_func_ushort : s->cu_func_ushort2;
            format = CU_AD_FORMAT_UNSIGNED_INT16;
            break;
        default:
            av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n", y->csp->name);
            goto exit;
        }
        av_log(ctx, AV_LOG_TRACE,
               "Deinterlacing plane %d: pixel_size: %d channels: %d\n",
               comp->plane, pixel_size, channels);
        call_kernel(ctx, func,
                    (CUdeviceptr)y->prev->data[i],
                    (CUdeviceptr)y->cur->data[i],
                    (CUdeviceptr)y->next->data[i],
                    format, channels,
                    AV_CEIL_RSHIFT(y->cur->width, i ? y->csp->log2_chroma_w : 0),
                    AV_CEIL_RSHIFT(y->cur->height, i ? y->csp->log2_chroma_h : 0),
                    y->cur->linesize[i],
                    (CUdeviceptr)dst->data[i],
                    AV_CEIL_RSHIFT(dst->width, i ? y->csp->log2_chroma_w : 0),
                    AV_CEIL_RSHIFT(dst->height, i ? y->csp->log2_chroma_h : 0),
                    dst->linesize[i] / comp->step,
                    parity, tff);
    }

exit:
    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
    return;
}