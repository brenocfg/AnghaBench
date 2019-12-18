#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_20__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;
typedef  struct TYPE_21__   TYPE_13__ ;

/* Type definitions */
struct TYPE_25__ {unsigned int BufferType; unsigned int DataSize; unsigned int CompressedBufferType; scalar_t__ NumMBsInBuffer; } ;
typedef  TYPE_2__ uint8_t ;
struct TYPE_21__ {unsigned int SliceBytesInBuffer; } ;
struct vp9_dxva2_picture_context {TYPE_13__ slice; int /*<<< orphan*/  bitstream; } ;
struct TYPE_26__ {TYPE_1__* frames; } ;
typedef  TYPE_3__ VP9SharedContext ;
struct TYPE_27__ {scalar_t__ pix_fmt; TYPE_3__* priv_data; } ;
struct TYPE_24__ {int /*<<< orphan*/  decoder; int /*<<< orphan*/  video_context; } ;
struct TYPE_23__ {struct vp9_dxva2_picture_context* hwaccel_picture_private; } ;
struct TYPE_22__ {int /*<<< orphan*/  decoder; } ;
typedef  TYPE_2__ DXVA2_DecodeBufferDesc ;
typedef  TYPE_2__ DECODER_BUFFER_DESC ;
typedef  TYPE_2__ D3D11_VIDEO_DECODER_BUFFER_DESC ;
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 size_t CUR_FRAME ; 
 TYPE_20__* D3D11VA_CONTEXT (int /*<<< orphan*/ *) ; 
 unsigned int D3D11_VIDEO_DECODER_BUFFER_BITSTREAM ; 
 unsigned int D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL ; 
 unsigned int DXVA2_BitStreamDateBufferType ; 
 TYPE_19__* DXVA2_CONTEXT (int /*<<< orphan*/ *) ; 
 unsigned int DXVA2_SliceControlBufferType ; 
 int /*<<< orphan*/ * DXVA_CONTEXT (TYPE_7__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 unsigned int FFMIN (int,unsigned int) ; 
 int /*<<< orphan*/  ID3D11VideoContext_GetDecoderBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*,void**) ; 
 int /*<<< orphan*/  ID3D11VideoContext_ReleaseDecoderBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  IDirectXVideoDecoder_GetBuffer (int /*<<< orphan*/ ,unsigned int,void**,unsigned int*) ; 
 int /*<<< orphan*/  IDirectXVideoDecoder_ReleaseBuffer (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int ff_dxva2_commit_buffer (TYPE_7__*,int /*<<< orphan*/ *,TYPE_2__*,unsigned int,TYPE_13__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_dxva2_is_d3d11 (TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int commit_bitstream_and_slice_buffer(AVCodecContext *avctx,
                                             DECODER_BUFFER_DESC *bs,
                                             DECODER_BUFFER_DESC *sc)
{
    const VP9SharedContext *h = avctx->priv_data;
    AVDXVAContext *ctx = DXVA_CONTEXT(avctx);
    struct vp9_dxva2_picture_context *ctx_pic = h->frames[CUR_FRAME].hwaccel_picture_private;
    void     *dxva_data_ptr;
    uint8_t  *dxva_data;
    unsigned dxva_size;
    unsigned padding;
    unsigned type;

#if CONFIG_D3D11VA
    if (ff_dxva2_is_d3d11(avctx)) {
        type = D3D11_VIDEO_DECODER_BUFFER_BITSTREAM;
        if (FAILED(ID3D11VideoContext_GetDecoderBuffer(D3D11VA_CONTEXT(ctx)->video_context,
                                                       D3D11VA_CONTEXT(ctx)->decoder,
                                                       type,
                                                       &dxva_size, &dxva_data_ptr)))
            return -1;
    }
#endif
#if CONFIG_DXVA2
    if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {
        type = DXVA2_BitStreamDateBufferType;
        if (FAILED(IDirectXVideoDecoder_GetBuffer(DXVA2_CONTEXT(ctx)->decoder,
                                                  type,
                                                  &dxva_data_ptr, &dxva_size)))
            return -1;
    }
#endif

    dxva_data = dxva_data_ptr;

    if (ctx_pic->slice.SliceBytesInBuffer > dxva_size) {
        av_log(avctx, AV_LOG_ERROR, "Failed to build bitstream");
        return -1;
    }

    memcpy(dxva_data, ctx_pic->bitstream, ctx_pic->slice.SliceBytesInBuffer);

    padding = FFMIN(128 - ((ctx_pic->slice.SliceBytesInBuffer) & 127), dxva_size - ctx_pic->slice.SliceBytesInBuffer);
    if (padding > 0) {
        memset(dxva_data + ctx_pic->slice.SliceBytesInBuffer, 0, padding);
        ctx_pic->slice.SliceBytesInBuffer += padding;
    }

#if CONFIG_D3D11VA
    if (ff_dxva2_is_d3d11(avctx))
        if (FAILED(ID3D11VideoContext_ReleaseDecoderBuffer(D3D11VA_CONTEXT(ctx)->video_context, D3D11VA_CONTEXT(ctx)->decoder, type)))
            return -1;
#endif
#if CONFIG_DXVA2
    if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD)
        if (FAILED(IDirectXVideoDecoder_ReleaseBuffer(DXVA2_CONTEXT(ctx)->decoder, type)))
            return -1;
#endif

#if CONFIG_D3D11VA
    if (ff_dxva2_is_d3d11(avctx)) {
        D3D11_VIDEO_DECODER_BUFFER_DESC *dsc11 = bs;
        memset(dsc11, 0, sizeof(*dsc11));
        dsc11->BufferType           = type;
        dsc11->DataSize             = ctx_pic->slice.SliceBytesInBuffer;
        dsc11->NumMBsInBuffer       = 0;

        type = D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL;
    }
#endif
#if CONFIG_DXVA2
    if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {
        DXVA2_DecodeBufferDesc *dsc2 = bs;
        memset(dsc2, 0, sizeof(*dsc2));
        dsc2->CompressedBufferType = type;
        dsc2->DataSize             = ctx_pic->slice.SliceBytesInBuffer;
        dsc2->NumMBsInBuffer       = 0;

        type = DXVA2_SliceControlBufferType;
    }
#endif

    return ff_dxva2_commit_buffer(avctx, ctx, sc,
                                  type,
                                  &ctx_pic->slice, sizeof(ctx_pic->slice), 0);
}