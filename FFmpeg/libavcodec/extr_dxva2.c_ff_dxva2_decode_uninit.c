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
struct TYPE_3__ {int nb_d3d11_views; scalar_t__ dxva2_service; scalar_t__* d3d11_views; int /*<<< orphan*/  decoder_ref; } ;
typedef  TYPE_1__ FFDXVASharedContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 TYPE_1__* DXVA_SHARED_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11VideoDecoderOutputView_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirectXVideoDecoderService_Release (scalar_t__) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (scalar_t__**) ; 

int ff_dxva2_decode_uninit(AVCodecContext *avctx)
{
    FFDXVASharedContext *sctx = DXVA_SHARED_CONTEXT(avctx);
    int i;

    av_buffer_unref(&sctx->decoder_ref);

#if CONFIG_D3D11VA
    for (i = 0; i < sctx->nb_d3d11_views; i++) {
        if (sctx->d3d11_views[i])
            ID3D11VideoDecoderOutputView_Release(sctx->d3d11_views[i]);
    }
    av_freep(&sctx->d3d11_views);
#endif

#if CONFIG_DXVA2
    if (sctx->dxva2_service)
        IDirectXVideoDecoderService_Release(sctx->dxva2_service);
#endif

    return 0;
}