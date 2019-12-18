#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ pix_fmt; } ;
struct TYPE_14__ {unsigned int BufferType; unsigned int DataSize; unsigned int NumMBsInBuffer; unsigned int CompressedBufferType; } ;
struct TYPE_13__ {int /*<<< orphan*/  decoder; int /*<<< orphan*/  video_context; } ;
struct TYPE_12__ {int /*<<< orphan*/  decoder; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DXVA2_DecodeBufferDesc ;
typedef  TYPE_1__ DECODER_BUFFER_DESC ;
typedef  TYPE_1__ D3D11_VIDEO_DECODER_BUFFER_DESC ;
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 TYPE_11__* D3D11VA_CONTEXT (int /*<<< orphan*/ *) ; 
 TYPE_10__* DXVA2_CONTEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ ID3D11VideoContext_GetDecoderBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*,void**) ; 
 scalar_t__ ID3D11VideoContext_ReleaseDecoderBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ IDirectXVideoDecoder_GetBuffer (int /*<<< orphan*/ ,unsigned int,void**,unsigned int*) ; 
 scalar_t__ IDirectXVideoDecoder_ReleaseBuffer (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 scalar_t__ ff_dxva2_is_d3d11 (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int ff_dxva2_commit_buffer(AVCodecContext *avctx,
                           AVDXVAContext *ctx,
                           DECODER_BUFFER_DESC *dsc,
                           unsigned type, const void *data, unsigned size,
                           unsigned mb_count)
{
    void     *dxva_data;
    unsigned dxva_size;
    int      result;
    HRESULT hr = 0;

#if CONFIG_D3D11VA
    if (ff_dxva2_is_d3d11(avctx))
        hr = ID3D11VideoContext_GetDecoderBuffer(D3D11VA_CONTEXT(ctx)->video_context,
                                                 D3D11VA_CONTEXT(ctx)->decoder,
                                                 type,
                                                 &dxva_size, &dxva_data);
#endif
#if CONFIG_DXVA2
    if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD)
        hr = IDirectXVideoDecoder_GetBuffer(DXVA2_CONTEXT(ctx)->decoder, type,
                                            &dxva_data, &dxva_size);
#endif
    if (FAILED(hr)) {
        av_log(avctx, AV_LOG_ERROR, "Failed to get a buffer for %u: 0x%x\n",
               type, (unsigned)hr);
        return -1;
    }
    if (size <= dxva_size) {
        memcpy(dxva_data, data, size);

#if CONFIG_D3D11VA
        if (ff_dxva2_is_d3d11(avctx)) {
            D3D11_VIDEO_DECODER_BUFFER_DESC *dsc11 = dsc;
            memset(dsc11, 0, sizeof(*dsc11));
            dsc11->BufferType           = type;
            dsc11->DataSize             = size;
            dsc11->NumMBsInBuffer       = mb_count;
        }
#endif
#if CONFIG_DXVA2
        if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {
            DXVA2_DecodeBufferDesc *dsc2 = dsc;
            memset(dsc2, 0, sizeof(*dsc2));
            dsc2->CompressedBufferType = type;
            dsc2->DataSize             = size;
            dsc2->NumMBsInBuffer       = mb_count;
        }
#endif

        result = 0;
    } else {
        av_log(avctx, AV_LOG_ERROR, "Buffer for type %u was too small\n", type);
        result = -1;
    }

#if CONFIG_D3D11VA
    if (ff_dxva2_is_d3d11(avctx))
        hr = ID3D11VideoContext_ReleaseDecoderBuffer(D3D11VA_CONTEXT(ctx)->video_context, D3D11VA_CONTEXT(ctx)->decoder, type);
#endif
#if CONFIG_DXVA2
    if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD)
        hr = IDirectXVideoDecoder_ReleaseBuffer(DXVA2_CONTEXT(ctx)->decoder, type);
#endif
    if (FAILED(hr)) {
        av_log(avctx, AV_LOG_ERROR,
               "Failed to release buffer type %u: 0x%x\n",
               type, (unsigned)hr);
        result = -1;
    }
    return result;
}