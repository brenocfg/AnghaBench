#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int quantiser_scale_code; int is_intra_slice; int /*<<< orphan*/  num_macroblocks; int /*<<< orphan*/  macroblock_address; } ;
typedef  TYPE_1__ VAEncSliceParameterBufferMPEG2 ;
struct TYPE_10__ {int /*<<< orphan*/  block_size; int /*<<< orphan*/  block_start; TYPE_1__* codec_slice_params; } ;
typedef  TYPE_2__ VAAPIEncodeSlice ;
struct TYPE_11__ {int type; } ;
typedef  TYPE_3__ VAAPIEncodePicture ;
struct TYPE_12__ {int quant_i; int quant_p; int quant_b; } ;
typedef  TYPE_4__ VAAPIEncodeMPEG2Context ;
struct TYPE_13__ {TYPE_4__* priv_data; } ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
#define  PICTURE_TYPE_B 131 
#define  PICTURE_TYPE_I 130 
#define  PICTURE_TYPE_IDR 129 
#define  PICTURE_TYPE_P 128 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static int vaapi_encode_mpeg2_init_slice_params(AVCodecContext *avctx,
                                               VAAPIEncodePicture *pic,
                                               VAAPIEncodeSlice *slice)
{
    VAAPIEncodeMPEG2Context            *priv = avctx->priv_data;
    VAEncSliceParameterBufferMPEG2   *vslice = slice->codec_slice_params;
    int qp;

    vslice->macroblock_address = slice->block_start;
    vslice->num_macroblocks    = slice->block_size;

    switch (pic->type) {
    case PICTURE_TYPE_IDR:
    case PICTURE_TYPE_I:
        qp = priv->quant_i;
        break;
    case PICTURE_TYPE_P:
        qp = priv->quant_p;
        break;
    case PICTURE_TYPE_B:
        qp = priv->quant_b;
        break;
    default:
        av_assert0(0 && "invalid picture type");
    }

    vslice->quantiser_scale_code = qp;
    vslice->is_intra_slice = (pic->type == PICTURE_TYPE_IDR ||
                              pic->type == PICTURE_TYPE_I);

    return 0;
}