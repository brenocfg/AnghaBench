#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* get_surface (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

unsigned ff_dxva2_get_surface_index(const AVCodecContext *avctx,
                                    const AVDXVAContext *ctx,
                                    const AVFrame *frame)
{
    void *surface = get_surface(avctx, frame);
    unsigned i;

#if CONFIG_D3D11VA
    if (avctx->pix_fmt == AV_PIX_FMT_D3D11)
        return (intptr_t)frame->data[1];
    if (avctx->pix_fmt == AV_PIX_FMT_D3D11VA_VLD) {
        D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC viewDesc;
        ID3D11VideoDecoderOutputView_GetDesc((ID3D11VideoDecoderOutputView*) surface, &viewDesc);
        return viewDesc.Texture2D.ArraySlice;
    }
#endif
#if CONFIG_DXVA2
    for (i = 0; i < DXVA_CONTEXT_COUNT(avctx, ctx); i++) {
        if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD && ctx->dxva2.surface[i] == surface)
            return i;
    }
#endif

    assert(0);
    return 0;
}