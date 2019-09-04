#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct dxva2_picture_context {unsigned int slice_count; TYPE_2__* slice; int /*<<< orphan*/ * bitstream; } ;
struct MpegEncContext {scalar_t__ picture_structure; int const mb_width; int const mb_height; TYPE_1__* current_picture_ptr; } ;
struct TYPE_11__ {struct MpegEncContext* priv_data; } ;
struct TYPE_10__ {unsigned int dwSliceDataLocation; int dwSliceBitsInBuffer; scalar_t__ wNumberMBsInSlice; } ;
struct TYPE_9__ {struct dxva2_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_2__ DXVA_SliceInfo ;
typedef  int /*<<< orphan*/  DECODER_BUFFER_DESC ;
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/ * DXVA_CONTEXT (TYPE_3__*) ; 
 scalar_t__ PICT_FRAME ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int ff_dxva2_commit_buffer (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,TYPE_2__*,int,unsigned int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int commit_bitstream_and_slice_buffer(AVCodecContext *avctx,
                                             DECODER_BUFFER_DESC *bs,
                                             DECODER_BUFFER_DESC *sc)
{
    const struct MpegEncContext *s = avctx->priv_data;
    AVDXVAContext *ctx = DXVA_CONTEXT(avctx);
    struct dxva2_picture_context *ctx_pic =
        s->current_picture_ptr->hwaccel_picture_private;
    const int is_field = s->picture_structure != PICT_FRAME;
    const unsigned mb_count = s->mb_width * (s->mb_height >> is_field);
    void     *dxva_data_ptr;
    uint8_t  *dxva_data, *current, *end;
    unsigned dxva_size;
    unsigned i;
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
    current = dxva_data;
    end = dxva_data + dxva_size;

    for (i = 0; i < ctx_pic->slice_count; i++) {
        DXVA_SliceInfo *slice = &ctx_pic->slice[i];
        unsigned position = slice->dwSliceDataLocation;
        unsigned size     = slice->dwSliceBitsInBuffer / 8;
        if (size > end - current) {
            av_log(avctx, AV_LOG_ERROR, "Failed to build bitstream");
            break;
        }
        slice->dwSliceDataLocation = current - dxva_data;

        if (i < ctx_pic->slice_count - 1)
            slice->wNumberMBsInSlice =
                slice[1].wNumberMBsInSlice - slice[0].wNumberMBsInSlice;
        else
            slice->wNumberMBsInSlice =
                mb_count - slice[0].wNumberMBsInSlice;

        memcpy(current, &ctx_pic->bitstream[position], size);
        current += size;
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
        dsc11->NumMBsInBuffer       = mb_count;

        type = D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL;
    }
#endif
#if CONFIG_DXVA2
    if (avctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {
        DXVA2_DecodeBufferDesc *dsc2 = bs;
        memset(dsc2, 0, sizeof(*dsc2));
        dsc2->CompressedBufferType = type;
        dsc2->DataSize             = current - dxva_data;
        dsc2->NumMBsInBuffer       = mb_count;

        type = DXVA2_SliceControlBufferType;
    }
#endif

    return ff_dxva2_commit_buffer(avctx, ctx, sc,
                                  type,
                                  ctx_pic->slice,
                                  ctx_pic->slice_count * sizeof(*ctx_pic->slice),
                                  mb_count);
}