#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  denoise ;
typedef  scalar_t__ VAStatus ;
struct TYPE_15__ {int /*<<< orphan*/  value; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ VAProcFilterParameterBuffer ;
struct TYPE_14__ {int /*<<< orphan*/  max_value; int /*<<< orphan*/  min_value; } ;
struct TYPE_16__ {TYPE_2__ range; } ;
typedef  TYPE_4__ VAProcFilterCap ;
struct TYPE_17__ {int /*<<< orphan*/  denoise; int /*<<< orphan*/  va_context; TYPE_1__* hwctx; } ;
typedef  TYPE_5__ VAAPIVPPContext ;
struct TYPE_18__ {TYPE_5__* priv; } ;
struct TYPE_13__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_5__ DenoiseVAAPIContext ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DENOISE_MAX ; 
 int /*<<< orphan*/  DENOISE_MIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  VAProcFilterNoiseReduction ; 
 int /*<<< orphan*/  VAProcFilterParameterBufferType ; 
 scalar_t__ VA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ff_vaapi_vpp_make_param_buffers (TYPE_7__*,int /*<<< orphan*/ ,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaErrorStr (scalar_t__) ; 
 scalar_t__ vaQueryVideoProcFilterCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int*) ; 

__attribute__((used)) static int denoise_vaapi_build_filter_params(AVFilterContext *avctx)
{
    VAAPIVPPContext *vpp_ctx = avctx->priv;
    DenoiseVAAPIContext *ctx = avctx->priv;

    VAProcFilterCap caps;

    VAStatus vas;
    uint32_t num_caps = 1;

    VAProcFilterParameterBuffer denoise;

    vas = vaQueryVideoProcFilterCaps(vpp_ctx->hwctx->display, vpp_ctx->va_context,
                                     VAProcFilterNoiseReduction,
                                     &caps, &num_caps);
    if (vas != VA_STATUS_SUCCESS) {
        av_log(avctx, AV_LOG_ERROR, "Failed to query denoise caps "
               "context: %d (%s).\n", vas, vaErrorStr(vas));
        return AVERROR(EIO);
    }

    denoise.type  = VAProcFilterNoiseReduction;
    denoise.value =  map(ctx->denoise, DENOISE_MIN, DENOISE_MAX,
                         caps.range.min_value,
                         caps.range.max_value);
    return ff_vaapi_vpp_make_param_buffers(avctx,
                                           VAProcFilterParameterBufferType,
                                           &denoise, sizeof(denoise), 1);
}