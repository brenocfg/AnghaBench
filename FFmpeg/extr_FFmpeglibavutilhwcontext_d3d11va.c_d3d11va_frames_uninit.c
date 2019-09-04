#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * texture; } ;
struct TYPE_8__ {TYPE_1__* internal; TYPE_4__* hwctx; } ;
struct TYPE_7__ {int /*<<< orphan*/ * staging_texture; } ;
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ D3D11VAFramesContext ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVD3D11VAFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11Texture2D_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    AVD3D11VAFramesContext *frames_hwctx = ctx->hwctx;
    D3D11VAFramesContext *s = ctx->internal->priv;

    if (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = NULL;

    if (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = NULL;
}