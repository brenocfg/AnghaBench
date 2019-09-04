#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  VdpVideoSurface ;
struct TYPE_7__ {int /*<<< orphan*/  (* surf_destroy ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ VDPAUDeviceContext ;
struct TYPE_8__ {TYPE_2__* device_ctx; } ;
struct TYPE_6__ {TYPE_1__* internal; } ;
struct TYPE_5__ {TYPE_3__* priv; } ;
typedef  TYPE_4__ AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdpau_buffer_free(void *opaque, uint8_t *data)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->internal->priv;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)data;

    device_priv->surf_destroy(surf);
}