#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;

/* Type definitions */
struct TYPE_29__ {TYPE_7__* priv_data; } ;
struct TYPE_28__ {unsigned int BSNALunitDataLocation; unsigned int SliceBytesInBuffer; int slice_type; int luma_log2_weight_denom; int chroma_log2_weight_denom; unsigned int num_ref_idx_l0_active_minus1; unsigned int num_ref_idx_l1_active_minus1; int slice_alpha_c0_offset_div2; int slice_beta_offset_div2; int**** Weights; int disable_deblocking_filter_idc; scalar_t__ slice_id; int /*<<< orphan*/  cabac_init_idc; int /*<<< orphan*/  direct_spatial_mv_pred_flag; int /*<<< orphan*/  redundant_pic_cnt; scalar_t__ slice_qp_delta; scalar_t__ slice_qs_delta; TYPE_13__** RefPicList; scalar_t__ Reserved8Bits; scalar_t__ BitOffsetToSliceData; scalar_t__ NumMbsForSlice; scalar_t__ first_mb_in_slice; scalar_t__ wBadSliceChopping; } ;
struct TYPE_22__ {TYPE_1__* pps; } ;
struct TYPE_27__ {int mb_width; scalar_t__ current_slice; TYPE_2__ ps; TYPE_5__* slice_ctx; } ;
struct TYPE_26__ {int /*<<< orphan*/  f; } ;
struct TYPE_24__ {int luma_log2_weight_denom; int chroma_log2_weight_denom; int*** luma_weight; int**** chroma_weight; scalar_t__* chroma_weight_flag; scalar_t__* luma_weight_flag; } ;
struct TYPE_25__ {int mb_y; int list_count; unsigned int* ref_count; int slice_alpha_c0_offset; int slice_beta_offset; scalar_t__ slice_type; int deblocking_filter; int /*<<< orphan*/  cabac_init_idc; int /*<<< orphan*/  direct_spatial_mv_pred; int /*<<< orphan*/  redundant_pic_count; scalar_t__ qscale; TYPE_4__ pwt; TYPE_3__** ref_list; scalar_t__ slice_type_fixed; int /*<<< orphan*/  gb; scalar_t__ mb_x; } ;
struct TYPE_23__ {scalar_t__ reference; TYPE_6__* parent; } ;
struct TYPE_21__ {scalar_t__ cabac; scalar_t__ init_qp; } ;
struct TYPE_20__ {int bPicEntry; } ;
typedef  TYPE_5__ H264SliceContext ;
typedef  TYPE_6__ H264Picture ;
typedef  TYPE_7__ H264Context ;
typedef  TYPE_8__ DXVA_Slice_H264_Long ;
typedef  int /*<<< orphan*/  DXVA_PicParams_H264 ;
typedef  int /*<<< orphan*/  AVDXVAContext ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int /*<<< orphan*/ * DXVA_CONTEXT (TYPE_9__*) ; 
 int DXVA_CONTEXT_WORKAROUND (TYPE_9__*,int /*<<< orphan*/ *) ; 
 unsigned int FF_ARRAY_ELEMS (TYPE_13__*) ; 
 int FF_DXVA2_WORKAROUND_INTEL_CLEARVIDEO ; 
 int FIELD_OR_MBAFF_PICTURE (TYPE_7__ const*) ; 
 scalar_t__ PICT_BOTTOM_FIELD ; 
 unsigned int ff_dxva2_get_surface_index (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_h264_get_slice_type (TYPE_5__*) ; 
 int /*<<< orphan*/  fill_picture_entry (TYPE_13__*,unsigned int,int) ; 
 scalar_t__ get_bits_count (int /*<<< orphan*/ *) ; 
 unsigned int get_refpic_index (int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_slice_long(AVCodecContext *avctx, DXVA_Slice_H264_Long *slice,
                            const DXVA_PicParams_H264 *pp, unsigned position, unsigned size)
{
    const H264Context *h = avctx->priv_data;
    H264SliceContext *sl = &h->slice_ctx[0];
    AVDXVAContext *ctx = DXVA_CONTEXT(avctx);
    unsigned list;

    memset(slice, 0, sizeof(*slice));
    slice->BSNALunitDataLocation = position;
    slice->SliceBytesInBuffer    = size;
    slice->wBadSliceChopping     = 0;

    slice->first_mb_in_slice     = (sl->mb_y >> FIELD_OR_MBAFF_PICTURE(h)) * h->mb_width + sl->mb_x;
    slice->NumMbsForSlice        = 0; /* XXX it is set once we have all slices */
    slice->BitOffsetToSliceData  = get_bits_count(&sl->gb) - 8;
    slice->slice_type            = ff_h264_get_slice_type(sl);
    if (sl->slice_type_fixed)
        slice->slice_type += 5;
    slice->luma_log2_weight_denom       = sl->pwt.luma_log2_weight_denom;
    slice->chroma_log2_weight_denom     = sl->pwt.chroma_log2_weight_denom;
    if (sl->list_count > 0)
        slice->num_ref_idx_l0_active_minus1 = sl->ref_count[0] - 1;
    if (sl->list_count > 1)
        slice->num_ref_idx_l1_active_minus1 = sl->ref_count[1] - 1;
    slice->slice_alpha_c0_offset_div2   = sl->slice_alpha_c0_offset / 2;
    slice->slice_beta_offset_div2       = sl->slice_beta_offset     / 2;
    slice->Reserved8Bits                = 0;

    for (list = 0; list < 2; list++) {
        unsigned i;
        for (i = 0; i < FF_ARRAY_ELEMS(slice->RefPicList[list]); i++) {
            if (list < sl->list_count && i < sl->ref_count[list]) {
                const H264Picture *r = sl->ref_list[list][i].parent;
                unsigned plane;
                unsigned index;
                if (DXVA_CONTEXT_WORKAROUND(avctx, ctx) & FF_DXVA2_WORKAROUND_INTEL_CLEARVIDEO)
                    index = ff_dxva2_get_surface_index(avctx, ctx, r->f);
                else
                    index = get_refpic_index(pp, ff_dxva2_get_surface_index(avctx, ctx, r->f));
                fill_picture_entry(&slice->RefPicList[list][i], index,
                                   sl->ref_list[list][i].reference == PICT_BOTTOM_FIELD);
                for (plane = 0; plane < 3; plane++) {
                    int w, o;
                    if (plane == 0 && sl->pwt.luma_weight_flag[list]) {
                        w = sl->pwt.luma_weight[i][list][0];
                        o = sl->pwt.luma_weight[i][list][1];
                    } else if (plane >= 1 && sl->pwt.chroma_weight_flag[list]) {
                        w = sl->pwt.chroma_weight[i][list][plane-1][0];
                        o = sl->pwt.chroma_weight[i][list][plane-1][1];
                    } else {
                        w = 1 << (plane == 0 ? sl->pwt.luma_log2_weight_denom :
                                               sl->pwt.chroma_log2_weight_denom);
                        o = 0;
                    }
                    slice->Weights[list][i][plane][0] = w;
                    slice->Weights[list][i][plane][1] = o;
                }
            } else {
                unsigned plane;
                slice->RefPicList[list][i].bPicEntry = 0xff;
                for (plane = 0; plane < 3; plane++) {
                    slice->Weights[list][i][plane][0] = 0;
                    slice->Weights[list][i][plane][1] = 0;
                }
            }
        }
    }
    slice->slice_qs_delta    = 0; /* XXX not implemented by FFmpeg */
    slice->slice_qp_delta    = sl->qscale - h->ps.pps->init_qp;
    slice->redundant_pic_cnt = sl->redundant_pic_count;
    if (sl->slice_type == AV_PICTURE_TYPE_B)
        slice->direct_spatial_mv_pred_flag = sl->direct_spatial_mv_pred;
    slice->cabac_init_idc = h->ps.pps->cabac ? sl->cabac_init_idc : 0;
    if (sl->deblocking_filter < 2)
        slice->disable_deblocking_filter_idc = 1 - sl->deblocking_filter;
    else
        slice->disable_deblocking_filter_idc = sl->deblocking_filter;
    slice->slice_id = h->current_slice - 1;
}