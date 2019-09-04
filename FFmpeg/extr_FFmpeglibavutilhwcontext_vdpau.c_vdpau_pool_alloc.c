#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  surf ;
typedef  scalar_t__ VdpVideoSurface ;
typedef  scalar_t__ VdpStatus ;
struct TYPE_13__ {int /*<<< orphan*/  chroma_type; } ;
typedef  TYPE_4__ VDPAUFramesContext ;
struct TYPE_14__ {scalar_t__ (* surf_create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  (* surf_destroy ) (scalar_t__) ;} ;
typedef  TYPE_5__ VDPAUDeviceContext ;
struct TYPE_16__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_3__* device_ctx; TYPE_1__* internal; } ;
struct TYPE_15__ {int /*<<< orphan*/  device; } ;
struct TYPE_12__ {TYPE_2__* internal; TYPE_6__* hwctx; } ;
struct TYPE_11__ {TYPE_5__* priv; } ;
struct TYPE_10__ {TYPE_4__* priv; } ;
typedef  TYPE_6__ AVVDPAUDeviceContext ;
typedef  TYPE_7__ AVHWFramesContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ VDP_STATUS_OK ; 
 int /*<<< orphan*/ * av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  vdpau_buffer_free ; 

__attribute__((used)) static AVBufferRef *vdpau_pool_alloc(void *opaque, int size)
{
    AVHWFramesContext             *ctx = opaque;
    VDPAUFramesContext           *priv = ctx->internal->priv;
    AVVDPAUDeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    VDPAUDeviceContext    *device_priv = ctx->device_ctx->internal->priv;

    AVBufferRef *ret;
    VdpVideoSurface surf;
    VdpStatus err;

    err = device_priv->surf_create(device_hwctx->device, priv->chroma_type,
                                   ctx->width, ctx->height, &surf);
    if (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        return NULL;
    }

    ret = av_buffer_create((uint8_t*)(uintptr_t)surf, sizeof(surf),
                           vdpau_buffer_free, ctx, AV_BUFFER_FLAG_READONLY);
    if (!ret) {
        device_priv->surf_destroy(surf);
        return NULL;
    }

    return ret;
}