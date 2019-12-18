#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {TYPE_1__* pVtbl; } ;
struct TYPE_11__ {int max_b_frames; TYPE_2__* priv_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  debug; TYPE_4__* factory; int /*<<< orphan*/  trace; int /*<<< orphan*/  version; int /*<<< orphan*/ * library; scalar_t__ dts_delay; int /*<<< orphan*/  timestamp_list; int /*<<< orphan*/  delayed_frame; } ;
struct TYPE_9__ {scalar_t__ (* GetTrace ) (TYPE_4__*,int /*<<< orphan*/ *) ;scalar_t__ (* GetDebug ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ AmfContext ;
typedef  TYPE_3__ AVCodecContext ;
typedef  scalar_t__ AMF_RESULT ;
typedef  scalar_t__ (* AMFQueryVersion_Fn ) (int /*<<< orphan*/ *) ;
typedef  scalar_t__ (* AMFInit_Fn ) (int /*<<< orphan*/ ,TYPE_4__**) ;

/* Variables and functions */
 scalar_t__ AMF_DLL_NAMEA ; 
 int /*<<< orphan*/  AMF_FULL_VERSION ; 
 int /*<<< orphan*/  AMF_INIT_FUNCTION_NAME ; 
 scalar_t__ AMF_OK ; 
 int /*<<< orphan*/  AMF_QUERY_VERSION_FUNCTION_NAME ; 
 int /*<<< orphan*/  AMF_RETURN_IF_FALSE (TYPE_2__*,int,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int RTLD_LOCAL ; 
 int RTLD_NOW ; 
 int /*<<< orphan*/  av_fifo_alloc (int) ; 
 int /*<<< orphan*/  av_frame_alloc () ; 
 int /*<<< orphan*/ * dlopen (scalar_t__,int) ; 
 scalar_t__ dlsym (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amf_load_library(AVCodecContext *avctx)
{
    AmfContext        *ctx = avctx->priv_data;
    AMFInit_Fn         init_fun;
    AMFQueryVersion_Fn version_fun;
    AMF_RESULT         res;

    ctx->delayed_frame = av_frame_alloc();
    if (!ctx->delayed_frame) {
        return AVERROR(ENOMEM);
    }
    // hardcoded to current HW queue size - will realloc in timestamp_queue_enqueue() if too small
    ctx->timestamp_list = av_fifo_alloc((avctx->max_b_frames + 16) * sizeof(int64_t));
    if (!ctx->timestamp_list) {
        return AVERROR(ENOMEM);
    }
    ctx->dts_delay = 0;


    ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(ctx, ctx->library != NULL,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(ctx, init_fun != NULL, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    version_fun = (AMFQueryVersion_Fn)dlsym(ctx->library, AMF_QUERY_VERSION_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(ctx, version_fun != NULL, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_VERSION_FUNCTION_NAME);

    res = version_fun(&ctx->version);
    AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_VERSION_FUNCTION_NAME, res);
    res = init_fun(AMF_FULL_VERSION, &ctx->factory);
    AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    res = ctx->factory->pVtbl->GetTrace(ctx->factory, &ctx->trace);
    AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR_UNKNOWN, "GetTrace() failed with error %d\n", res);
    res = ctx->factory->pVtbl->GetDebug(ctx->factory, &ctx->debug);
    AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR_UNKNOWN, "GetDebug() failed with error %d\n", res);
    return 0;
}