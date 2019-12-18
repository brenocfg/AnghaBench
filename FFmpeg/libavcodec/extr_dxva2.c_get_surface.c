#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ format; void** data; } ;
struct TYPE_5__ {intptr_t nb_d3d11_views; void** d3d11_views; int /*<<< orphan*/ * d3d11_texture; } ;
typedef  int /*<<< orphan*/  ID3D11Texture2D ;
typedef  TYPE_1__ FFDXVASharedContext ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_D3D11 ; 
 TYPE_1__* DXVA_SHARED_CONTEXT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 

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