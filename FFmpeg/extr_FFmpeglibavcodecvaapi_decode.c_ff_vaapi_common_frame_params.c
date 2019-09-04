#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VAConfigID ;
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__* hwctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  device_ref; TYPE_3__* device_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ AVVAAPIDeviceContext ;
typedef  TYPE_2__ AVHWFramesContext ;
typedef  TYPE_3__ AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  TYPE_4__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_HWDEVICE_TYPE_VAAPI ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ VA_INVALID_ID ; 
 int /*<<< orphan*/  vaDestroyConfig (int /*<<< orphan*/ ,scalar_t__) ; 
 int vaapi_decode_make_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,TYPE_4__*) ; 

int ff_vaapi_common_frame_params(AVCodecContext *avctx,
                                 AVBufferRef *hw_frames_ctx)
{
    AVHWFramesContext *hw_frames = (AVHWFramesContext *)hw_frames_ctx->data;
    AVHWDeviceContext *device_ctx = hw_frames->device_ctx;
    AVVAAPIDeviceContext *hwctx;
    VAConfigID va_config = VA_INVALID_ID;
    int err;

    if (device_ctx->type != AV_HWDEVICE_TYPE_VAAPI)
        return AVERROR(EINVAL);
    hwctx = device_ctx->hwctx;

    err = vaapi_decode_make_config(avctx, hw_frames->device_ref, &va_config,
                                   hw_frames_ctx);
    if (err)
        return err;

    if (va_config != VA_INVALID_ID)
        vaDestroyConfig(hwctx->display, va_config);

    return 0;
}