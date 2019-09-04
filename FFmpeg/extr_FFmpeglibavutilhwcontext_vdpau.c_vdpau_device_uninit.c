#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * pix_fmts; } ;
typedef  TYPE_2__ VDPAUDeviceContext ;
struct TYPE_7__ {TYPE_1__* internal; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ AVHWDeviceContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->internal->priv;
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}