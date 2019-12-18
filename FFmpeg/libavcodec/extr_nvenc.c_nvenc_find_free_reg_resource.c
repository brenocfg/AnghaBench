#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * regptr; int /*<<< orphan*/ * ptr; int /*<<< orphan*/  mapped; } ;
struct TYPE_12__ {TYPE_2__* priv_data; } ;
struct TYPE_11__ {scalar_t__ (* nvEncUnregisterResource ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_3__ nvenc_funcs; } ;
struct TYPE_10__ {int nb_registered_frames; TYPE_8__* registered_frames; int /*<<< orphan*/  nvencoder; TYPE_1__ nvenc_dload_funcs; } ;
typedef  TYPE_1__ NvencDynLoadFunctions ;
typedef  TYPE_2__ NvencContext ;
typedef  TYPE_3__ NV_ENCODE_API_FUNCTION_LIST ;
typedef  scalar_t__ NVENCSTATUS ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (TYPE_8__*) ; 
 scalar_t__ NV_ENC_SUCCESS ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int nvenc_print_error (TYPE_4__*,scalar_t__,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvenc_find_free_reg_resource(AVCodecContext *avctx)
{
    NvencContext *ctx = avctx->priv_data;
    NvencDynLoadFunctions *dl_fn = &ctx->nvenc_dload_funcs;
    NV_ENCODE_API_FUNCTION_LIST *p_nvenc = &dl_fn->nvenc_funcs;
    NVENCSTATUS nv_status;

    int i, first_round;

    if (ctx->nb_registered_frames == FF_ARRAY_ELEMS(ctx->registered_frames)) {
        for (first_round = 1; first_round >= 0; first_round--) {
            for (i = 0; i < ctx->nb_registered_frames; i++) {
                if (!ctx->registered_frames[i].mapped) {
                    if (ctx->registered_frames[i].regptr) {
                        if (first_round)
                            continue;
                        nv_status = p_nvenc->nvEncUnregisterResource(ctx->nvencoder, ctx->registered_frames[i].regptr);
                        if (nv_status != NV_ENC_SUCCESS)
                            return nvenc_print_error(avctx, nv_status, "Failed unregistering unused input resource");
                        ctx->registered_frames[i].ptr = NULL;
                        ctx->registered_frames[i].regptr = NULL;
                    }
                    return i;
                }
            }
        }
    } else {
        return ctx->nb_registered_frames++;
    }

    av_log(avctx, AV_LOG_ERROR, "Too many registered CUDA frames\n");
    return AVERROR(ENOMEM);
}