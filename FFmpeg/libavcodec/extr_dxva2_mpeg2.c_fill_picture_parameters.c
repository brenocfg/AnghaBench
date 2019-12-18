#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  f; } ;
struct TYPE_7__ {int /*<<< orphan*/  f; } ;
struct MpegEncContext {int picture_structure; scalar_t__ pict_type; int mb_height; int alternate_scan; int** mpeg_f_code; int intra_dc_precision; int top_field_first; int frame_pred_frame_dct; int concealment_motion_vectors; int q_scale_type; int intra_vlc_format; int repeat_first_field; int chroma_420_type; int progressive_frame; int /*<<< orphan*/  chroma_format; int /*<<< orphan*/  first_field; scalar_t__ mb_width; TYPE_2__ next_picture; TYPE_1__ last_picture; TYPE_3__* current_picture_ptr; } ;
struct TYPE_10__ {int wForwardRefPictureIndex; int wBackwardRefPictureIndex; int wPicHeightInMBminus1; int bMacroblockWidthMinus1; int bMacroblockHeightMinus1; int bBlockWidthMinus1; int bBlockHeightMinus1; int bBPPminus1; int bPicStructure; int bSecondField; int bPicIntra; int bPicBackwardPrediction; int bPicScanFixed; int bPicScanMethod; int wBitstreamFcodes; int wBitstreamPCEelements; scalar_t__ bBitstreamConcealmentMethod; scalar_t__ bBitstreamConcealmentNeed; scalar_t__ bReservedBits; scalar_t__ bMV_RPS; scalar_t__ bPicBinPB; scalar_t__ bPicOBMC; scalar_t__ bPic4MVallowed; scalar_t__ bPicDeblockConfined; scalar_t__ bPicDeblocked; scalar_t__ bPicExtrapolation; scalar_t__ bPicOverflowBlocks; scalar_t__ bPicSpatialResid8; scalar_t__ bRcontrol; scalar_t__ bPicReadbackRequests; int /*<<< orphan*/  bChromaFormat; scalar_t__ bMVprecisionAndChromaRelation; scalar_t__ bBidirectionalAveragingMode; scalar_t__ wPicWidthInMBminus1; scalar_t__ wDeblockedPictureIndex; void* wDecodedPictureIndex; } ;
struct TYPE_9__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_3__ Picture ;
typedef  TYPE_4__ DXVA_PictureParameters ;
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int PICT_FRAME ; 
 void* ff_dxva2_get_surface_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_picture_parameters(AVCodecContext *avctx,
                                    AVDXVAContext *ctx,
                                    const struct MpegEncContext *s,
                                    DXVA_PictureParameters *pp)
{
    const Picture *current_picture = s->current_picture_ptr;
    int is_field = s->picture_structure != PICT_FRAME;

    memset(pp, 0, sizeof(*pp));
    pp->wDecodedPictureIndex         = ff_dxva2_get_surface_index(avctx, ctx, current_picture->f);
    pp->wDeblockedPictureIndex       = 0;
    if (s->pict_type != AV_PICTURE_TYPE_I)
        pp->wForwardRefPictureIndex  = ff_dxva2_get_surface_index(avctx, ctx, s->last_picture.f);
    else
        pp->wForwardRefPictureIndex  = 0xffff;
    if (s->pict_type == AV_PICTURE_TYPE_B)
        pp->wBackwardRefPictureIndex = ff_dxva2_get_surface_index(avctx, ctx, s->next_picture.f);
    else
        pp->wBackwardRefPictureIndex = 0xffff;
    pp->wPicWidthInMBminus1          = s->mb_width  - 1;
    pp->wPicHeightInMBminus1         = (s->mb_height >> is_field) - 1;
    pp->bMacroblockWidthMinus1       = 15;
    pp->bMacroblockHeightMinus1      = 15;
    pp->bBlockWidthMinus1            = 7;
    pp->bBlockHeightMinus1           = 7;
    pp->bBPPminus1                   = 7;
    pp->bPicStructure                = s->picture_structure;
    pp->bSecondField                 = is_field && !s->first_field;
    pp->bPicIntra                    = s->pict_type == AV_PICTURE_TYPE_I;
    pp->bPicBackwardPrediction       = s->pict_type == AV_PICTURE_TYPE_B;
    pp->bBidirectionalAveragingMode  = 0;
    pp->bMVprecisionAndChromaRelation= 0; /* FIXME */
    pp->bChromaFormat                = s->chroma_format;
    pp->bPicScanFixed                = 1;
    pp->bPicScanMethod               = s->alternate_scan ? 1 : 0;
    pp->bPicReadbackRequests         = 0;
    pp->bRcontrol                    = 0;
    pp->bPicSpatialResid8            = 0;
    pp->bPicOverflowBlocks           = 0;
    pp->bPicExtrapolation            = 0;
    pp->bPicDeblocked                = 0;
    pp->bPicDeblockConfined          = 0;
    pp->bPic4MVallowed               = 0;
    pp->bPicOBMC                     = 0;
    pp->bPicBinPB                    = 0;
    pp->bMV_RPS                      = 0;
    pp->bReservedBits                = 0;
    pp->wBitstreamFcodes             = (s->mpeg_f_code[0][0] << 12) |
                                       (s->mpeg_f_code[0][1] <<  8) |
                                       (s->mpeg_f_code[1][0] <<  4) |
                                       (s->mpeg_f_code[1][1]      );
    pp->wBitstreamPCEelements        = (s->intra_dc_precision         << 14) |
                                       (s->picture_structure          << 12) |
                                       (s->top_field_first            << 11) |
                                       (s->frame_pred_frame_dct       << 10) |
                                       (s->concealment_motion_vectors <<  9) |
                                       (s->q_scale_type               <<  8) |
                                       (s->intra_vlc_format           <<  7) |
                                       (s->alternate_scan             <<  6) |
                                       (s->repeat_first_field         <<  5) |
                                       (s->chroma_420_type            <<  4) |
                                       (s->progressive_frame          <<  3);
    pp->bBitstreamConcealmentNeed    = 0;
    pp->bBitstreamConcealmentMethod  = 0;
}