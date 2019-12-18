#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
struct hevc_dxva2_picture_context {unsigned int slice_count; int const* bitstream; TYPE_3__* slice_short; } ;
typedef  int /*<<< orphan*/  start_code ;
struct TYPE_17__ {scalar_t__ pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_16__ {unsigned int BSNALunitDataLocation; unsigned int SliceBytesInBuffer; } ;
struct TYPE_15__ {TYPE_1__* ref; } ;
struct TYPE_14__ {struct hevc_dxva2_picture_context* hwaccel_picture_private; } ;
struct TYPE_13__ {int /*<<< orphan*/  decoder; int /*<<< orphan*/  video_context; } ;
struct TYPE_12__ {int /*<<< orphan*/  decoder; } ;
typedef  TYPE_1__ HEVCFrame ;
typedef  TYPE_2__ HEVCContext ;
typedef  TYPE_3__ DXVA_Slice_HEVC_Short ;
typedef  int DXVA2_DecodeBufferDesc ;
typedef  int DECODER_BUFFER_DESC ;
typedef  int D3D11_VIDEO_DECODER_BUFFER_DESC ;
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 TYPE_11__* D3D11VA_CONTEXT (int /*<<< orphan*/ *) ; 
 unsigned int D3D11_VIDEO_DECODER_BUFFER_BITSTREAM ; 
 unsigned int D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL ; 
 unsigned int DXVA2_BitStreamDateBufferType ; 
 TYPE_10__* DXVA2_CONTEXT (int /*<<< orphan*/ *) ; 
 unsigned int DXVA2_SliceControlBufferType ; 
 int /*<<< orphan*/ * DXVA_CONTEXT (TYPE_4__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 unsigned int FFMIN (int,int) ; 
 int /*<<< orphan*/  ID3D11VideoContext_GetDecoderBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*,void**) ; 
 int /*<<< orphan*/  ID3D11VideoContext_ReleaseDecoderBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  IDirectXVideoDecoder_GetBuffer (int /*<<< orphan*/ ,unsigned int,void**,unsigned int*) ; 
 int /*<<< orphan*/  IDirectXVideoDecoder_ReleaseBuffer (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_dxva2_commit_buffer (TYPE_4__*,int /*<<< orphan*/ *,int*,unsigned int,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_dxva2_is_d3d11 (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,unsigned int const) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int commit_bitstream_and_slice_buffer(AVCodecContext *avctx,
                                             DECODER_BUFFER_DESC *bs,
                                             DECODER_BUFFER_DESC *sc)
{
    const HEVCContext *h = avctx->priv_data;
    AVDXVAContext *ctx = DXVA_CONTEXT(avctx);
    const HEVCFrame *current_picture = h->ref;
    struct hevc_dxva2_picture_context *ctx_pic = current_picture->hwaccel_picture_private;
    DXVA_Slice_HEVC_Short *slice = NULL;
    void     *dxva_data_ptr;
    uint8_t  *dxva_data, *current, *end;
    unsigned dxva_size;
    void     *slice_data;
    unsigned slice_size;
    unsigned padding;
    unsigned i;
    unsigned type;

    /* Create an annex B bitstream buffer with only slice NAL and finalize slice */
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
    current = dxva_data;
    end = dxva_data + dxva_size;

    for (i = 0; i < ctx_pic->slice_count; i++) {
        static const uint8_t start_code[] = { 0, 0, 1 };
        static const unsigned start_code_size = sizeof(start_code);
        unsigned position, size;

        slice = &ctx_pic->slice_short[i];

        position = slice->BSNALunitDataLocation;
        size     = slice->SliceBytesInBuffer;
        if (start_code_size + size > end - current) {
            av_log(avctx, AV_LOG_ERROR, "Failed to build bitstream");
            break;
        }

        slice->BSNALunitDataLocation = current - dxva_data;
        slice->SliceBytesInBuffer    = start_code_size + size;

        memcpy(current, start_code, start_code_size);
        current += start_code_size;

        memcpy(current, &ctx_pic->bitstream[position], size);
        current += size;
    }
    padding = FFMIN(128 - ((current - dxva_data) & 127), end - current);
    if (slice && padding > 0) {
        memset(current, 0, padding);
        current += padding;

        slice->SliceBytesInBuffer += padding;
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
    if (i < ctx_pic->slice_count)
        return -1;

#if CONFIG_D3D11VA
    if (ff_dxva2_is_d3d11(avctx)) {
        D3D11_VIDEO_DECODER_BUFFER_DESC *dsc11 = bs;
        memset(dsc11, 0, sizeof(*dsc11));
        dsc11->BufferType           = type;
        dsc11->DataSize             = current - dxva_data;
        dsc11->NumMBsInBuffer       = 0;

        type = D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL;
    }
#endif
#if CONFIG_DXVA2
    if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {
        DXVA2_DecodeBufferDesc *dsc2 = bs;
        memset(dsc2, 0, sizeof(*dsc2));
        dsc2->CompressedBufferType = type;
        dsc2->DataSize             = current - dxva_data;
        dsc2->NumMBsInBuffer       = 0;

        type = DXVA2_SliceControlBufferType;
    }
#endif

    slice_data = ctx_pic->slice_short;
    slice_size = ctx_pic->slice_count * sizeof(*ctx_pic->slice_short);

    av_assert0(((current - dxva_data) & 127) == 0);
    return ff_dxva2_commit_buffer(avctx, ctx, sc,
                                  type,
                                  slice_data, slice_size, 0);
}