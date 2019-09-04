#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {size_t n; size_t n_frames; int /*<<< orphan*/  cu_stream; scalar_t__ data; TYPE_4__* hwctx; TYPE_3__* frames; TYPE_2__* hw_frames_ctx; } ;
typedef  TYPE_5__ ThumbnailCudaContext ;
struct TYPE_25__ {TYPE_10__* dst; } ;
struct TYPE_24__ {scalar_t__ sw_format; } ;
struct TYPE_23__ {int* dstHost; int srcPitch; int dstPitch; int WidthInBytes; int Height; scalar_t__ srcDevice; int /*<<< orphan*/  dstMemoryType; int /*<<< orphan*/  srcMemoryType; int /*<<< orphan*/  member_0; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuMemcpy2DAsync ) (TYPE_7__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuMemsetD8Async ) (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  cuda_ctx; TYPE_1__* internal; } ;
struct TYPE_19__ {int* histogram; int /*<<< orphan*/ * buf; } ;
struct TYPE_18__ {scalar_t__ data; } ;
struct TYPE_17__ {TYPE_6__* cuda_dl; } ;
struct TYPE_16__ {TYPE_9__** outputs; TYPE_5__* priv; } ;
typedef  TYPE_6__ CudaFunctions ;
typedef  int /*<<< orphan*/  CUcontext ;
typedef  TYPE_7__ CUDA_MEMCPY2D ;
typedef  TYPE_8__ AVHWFramesContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_9__ AVFilterLink ;
typedef  TYPE_10__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_NV12 ; 
 scalar_t__ AV_PIX_FMT_P010LE ; 
 scalar_t__ AV_PIX_FMT_P016LE ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CU_MEMORYTYPE_DEVICE ; 
 int /*<<< orphan*/  CU_MEMORYTYPE_HOST ; 
 int HIST_SIZE ; 
 int ff_filter_frame (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_best_frame (TYPE_10__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thumbnail (TYPE_10__*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx  = inlink->dst;
    ThumbnailCudaContext *s   = ctx->priv;
    CudaFunctions *cu = s->hwctx->internal->cuda_dl;
    AVFilterLink *outlink = ctx->outputs[0];
    int *hist = s->frames[s->n].histogram;
    AVHWFramesContext *hw_frames_ctx = (AVHWFramesContext*)s->hw_frames_ctx->data;
    CUcontext dummy;
    CUDA_MEMCPY2D cpy = { 0 };
    int ret = 0;

    // keep a reference of each frame
    s->frames[s->n].buf = frame;

    ret = CHECK_CU(cu->cuCtxPushCurrent(s->hwctx->cuda_ctx));
    if (ret < 0)
        return ret;

    CHECK_CU(cu->cuMemsetD8Async(s->data, 0, HIST_SIZE * sizeof(int), s->cu_stream));

    thumbnail(ctx, (int*)s->data, frame);

    cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
    cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
    cpy.srcDevice = s->data;
    cpy.dstHost = hist;
    cpy.srcPitch = HIST_SIZE * sizeof(int);
    cpy.dstPitch = HIST_SIZE * sizeof(int);
    cpy.WidthInBytes = HIST_SIZE * sizeof(int);
    cpy.Height = 1;

    ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, s->cu_stream));
    if (ret < 0)
        return ret;

    if (hw_frames_ctx->sw_format == AV_PIX_FMT_NV12 || hw_frames_ctx->sw_format == AV_PIX_FMT_YUV420P ||
        hw_frames_ctx->sw_format == AV_PIX_FMT_P010LE || hw_frames_ctx->sw_format == AV_PIX_FMT_P016LE)
    {
        int i;
        for (i = 256; i < HIST_SIZE; i++)
            hist[i] = 4 * hist[i];
    }

    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
    if (ret < 0)
        return ret;

    // no selection until the buffer of N frames is filled up
    s->n++;
    if (s->n < s->n_frames)
        return 0;

    return ff_filter_frame(outlink, get_best_frame(ctx));
}