#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int** f_code; scalar_t__ temporal_reference; int /*<<< orphan*/  backward_reference_picture; int /*<<< orphan*/  forward_reference_picture; int /*<<< orphan*/  picture_type; int /*<<< orphan*/  coded_buf; int /*<<< orphan*/  reconstructed_picture; } ;
typedef  TYPE_4__ VAEncPictureParameterBufferMPEG2 ;
struct TYPE_16__ {int type; TYPE_3__** refs; int /*<<< orphan*/  output_buffer; int /*<<< orphan*/  recon_surface; scalar_t__ display_order; TYPE_4__* codec_picture_params; } ;
typedef  TYPE_5__ VAAPIEncodePicture ;
struct TYPE_19__ {int** f_code; } ;
struct TYPE_12__ {TYPE_8__ picture_coding; } ;
struct TYPE_13__ {TYPE_1__ data; } ;
struct TYPE_18__ {int picture_coding_type; scalar_t__ temporal_reference; } ;
struct TYPE_17__ {int f_code_horizontal; int f_code_vertical; scalar_t__ last_i_frame; TYPE_2__ picture_coding_extension; TYPE_7__ picture_header; } ;
typedef  TYPE_6__ VAAPIEncodeMPEG2Context ;
struct TYPE_20__ {TYPE_6__* priv_data; } ;
struct TYPE_14__ {int /*<<< orphan*/  recon_surface; } ;
typedef  TYPE_7__ MPEG2RawPictureHeader ;
typedef  TYPE_8__ MPEG2RawPictureCodingExtension ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
#define  PICTURE_TYPE_B 131 
#define  PICTURE_TYPE_I 130 
#define  PICTURE_TYPE_IDR 129 
#define  PICTURE_TYPE_P 128 
 int /*<<< orphan*/  VAEncPictureTypeBidirectional ; 
 int /*<<< orphan*/  VAEncPictureTypeIntra ; 
 int /*<<< orphan*/  VAEncPictureTypePredictive ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static int vaapi_encode_mpeg2_init_picture_params(AVCodecContext *avctx,
                                                 VAAPIEncodePicture *pic)
{
    VAAPIEncodeMPEG2Context          *priv = avctx->priv_data;
    MPEG2RawPictureHeader              *ph = &priv->picture_header;
    MPEG2RawPictureCodingExtension    *pce = &priv->picture_coding_extension.data.picture_coding;
    VAEncPictureParameterBufferMPEG2 *vpic = pic->codec_picture_params;

    if (pic->type == PICTURE_TYPE_IDR || pic->type == PICTURE_TYPE_I) {
        ph->temporal_reference  = 0;
        ph->picture_coding_type = 1;
        priv->last_i_frame = pic->display_order;
    } else {
        ph->temporal_reference = pic->display_order - priv->last_i_frame;
        ph->picture_coding_type = pic->type == PICTURE_TYPE_B ? 3 : 2;
    }

    if (pic->type == PICTURE_TYPE_P || pic->type == PICTURE_TYPE_B) {
        pce->f_code[0][0] = priv->f_code_horizontal;
        pce->f_code[0][1] = priv->f_code_vertical;
    } else {
        pce->f_code[0][0] = 15;
        pce->f_code[0][1] = 15;
    }
    if (pic->type == PICTURE_TYPE_B) {
        pce->f_code[1][0] = priv->f_code_horizontal;
        pce->f_code[1][1] = priv->f_code_vertical;
    } else {
        pce->f_code[1][0] = 15;
        pce->f_code[1][1] = 15;
    }

    vpic->reconstructed_picture = pic->recon_surface;
    vpic->coded_buf             = pic->output_buffer;

    switch (pic->type) {
    case PICTURE_TYPE_IDR:
    case PICTURE_TYPE_I:
        vpic->picture_type = VAEncPictureTypeIntra;
        break;
    case PICTURE_TYPE_P:
        vpic->picture_type = VAEncPictureTypePredictive;
        vpic->forward_reference_picture = pic->refs[0]->recon_surface;
        break;
    case PICTURE_TYPE_B:
        vpic->picture_type = VAEncPictureTypeBidirectional;
        vpic->forward_reference_picture  = pic->refs[0]->recon_surface;
        vpic->backward_reference_picture = pic->refs[1]->recon_surface;
        break;
    default:
        av_assert0(0 && "invalid picture type");
    }

    vpic->temporal_reference = ph->temporal_reference;
    vpic->f_code[0][0]       = pce->f_code[0][0];
    vpic->f_code[0][1]       = pce->f_code[0][1];
    vpic->f_code[1][0]       = pce->f_code[1][0];
    vpic->f_code[1][1]       = pce->f_code[1][1];

    return 0;
}