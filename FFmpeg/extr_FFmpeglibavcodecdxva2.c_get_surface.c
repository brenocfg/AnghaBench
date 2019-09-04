#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void** data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */

__attribute__((used)) static void *get_surface(const AVCodecContext *avctx, const AVFrame *frame)
{
#if CONFIG_D3D11VA
    if (frame->format == AV_PIX_FMT_D3D11) {
        FFDXVASharedContext *sctx = DXVA_SHARED_CONTEXT(avctx);
        intptr_t index = (intptr_t)frame->data[1];
        if (index < 0 || index >= sctx->nb_d3d11_views ||
            sctx->d3d11_texture != (ID3D11Texture2D *)frame->data[0]) {
            av_log((void *)avctx, AV_LOG_ERROR, "get_buffer frame is invalid!\n");
            return NULL;
        }
        return sctx->d3d11_views[index];
    }
#endif
    return frame->data[3];
}