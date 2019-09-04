#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_9__ ;
typedef  struct TYPE_52__   TYPE_8__ ;
typedef  struct TYPE_51__   TYPE_7__ ;
typedef  struct TYPE_50__   TYPE_6__ ;
typedef  struct TYPE_49__   TYPE_5__ ;
typedef  struct TYPE_48__   TYPE_4__ ;
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_31__ ;
typedef  struct TYPE_45__   TYPE_2__ ;
typedef  struct TYPE_44__   TYPE_1__ ;
typedef  struct TYPE_43__   TYPE_19__ ;
typedef  struct TYPE_42__   TYPE_18__ ;
typedef  struct TYPE_41__   TYPE_17__ ;
typedef  struct TYPE_40__   TYPE_16__ ;
typedef  struct TYPE_39__   TYPE_15__ ;
typedef  struct TYPE_38__   TYPE_14__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
struct TYPE_53__ {TYPE_8__* f; } ;
struct TYPE_52__ {TYPE_7__** buf; } ;
struct TYPE_51__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_50__ {TYPE_5__* f; } ;
struct TYPE_49__ {TYPE_4__** buf; } ;
struct TYPE_48__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_47__ {TYPE_2__* sps; TYPE_1__* pps; } ;
struct TYPE_46__ {scalar_t__ skip_loop_filter; int flags2; int debug; } ;
struct TYPE_45__ {int bit_depth_luma; } ;
struct TYPE_44__ {int weighted_bipred_idc; int /*<<< orphan*/ * chroma_qp_index_offset; } ;
struct TYPE_43__ {scalar_t__ type; scalar_t__ ref_idc; } ;
struct TYPE_38__ {int /*<<< orphan*/  frame_num; } ;
struct TYPE_42__ {int mb_num; int mb_width; int mb_height; scalar_t__ picture_structure; scalar_t__ nal_unit_type; int nb_slice_ctx; int postpone_filter; int current_slice; int* slice_row; int*** ref2frm; int short_ref_count; int long_ref_count; TYPE_15__* cur_pic_ptr; TYPE_14__ poc; TYPE_31__* avctx; TYPE_12__** long_ref; TYPE_9__** short_ref; TYPE_3__ ps; int /*<<< orphan*/  setup_finished; scalar_t__ picture_idr; } ;
struct TYPE_40__ {int use_weight; scalar_t__ use_weight_chroma; } ;
struct TYPE_41__ {int first_mb_addr; int resync_mb_x; int mb_x; int resync_mb_y; int mb_y; scalar_t__ slice_type_nos; int deblocking_filter; int qp_thresh; int slice_num; int list_count; int* ref_count; scalar_t__ slice_type; scalar_t__ direct_spatial_mv_pred; TYPE_16__ pwt; int /*<<< orphan*/  slice_beta_offset; int /*<<< orphan*/  slice_alpha_c0_offset; int /*<<< orphan*/  qscale; scalar_t__ slice_type_fixed; TYPE_13__** ref_list; } ;
struct TYPE_39__ {int /*<<< orphan*/ * field_poc; } ;
struct TYPE_37__ {int reference; TYPE_6__* parent; } ;
struct TYPE_36__ {TYPE_11__* f; } ;
struct TYPE_35__ {TYPE_10__** buf; } ;
struct TYPE_34__ {int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_17__ H264SliceContext ;
typedef  TYPE_18__ H264Context ;
typedef  TYPE_19__ H2645NAL ;
typedef  int /*<<< orphan*/  AVBuffer ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 scalar_t__ AVDISCARD_BIDIR ; 
 scalar_t__ AVDISCARD_NONINTRA ; 
 scalar_t__ AVDISCARD_NONKEY ; 
 scalar_t__ AVDISCARD_NONREF ; 
 int AVERROR_INVALIDDATA ; 
 int AV_CODEC_FLAG2_FAST ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int FFMAX3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FF_DEBUG_PICT_INFO ; 
 int FIELD_OR_MBAFF_PICTURE (TYPE_18__*) ; 
 scalar_t__ FRAME_MBAFF (TYPE_18__*) ; 
 scalar_t__ H264_NAL_IDR_SLICE ; 
 int MAX_SLICES ; 
 scalar_t__ PICT_BOTTOM_FIELD ; 
 scalar_t__ PICT_FRAME ; 
 scalar_t__ PICT_TOP_FIELD ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_get_picture_type_char (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_31__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_h264_build_ref_list (TYPE_18__*,TYPE_17__*) ; 
 int /*<<< orphan*/  ff_h264_direct_dist_scale_factor (TYPE_18__*,TYPE_17__*) ; 
 int /*<<< orphan*/  ff_h264_direct_ref_list_init (TYPE_18__*,TYPE_17__*) ; 
 int /*<<< orphan*/  implicit_weight_table (TYPE_18__*,TYPE_17__*,int) ; 

__attribute__((used)) static int h264_slice_init(H264Context *h, H264SliceContext *sl,
                           const H2645NAL *nal)
{
    int i, j, ret = 0;

    if (h->picture_idr && nal->type != H264_NAL_IDR_SLICE) {
        av_log(h->avctx, AV_LOG_ERROR, "Invalid mix of IDR and non-IDR slices\n");
        return AVERROR_INVALIDDATA;
    }

    av_assert1(h->mb_num == h->mb_width * h->mb_height);
    if (sl->first_mb_addr << FIELD_OR_MBAFF_PICTURE(h) >= h->mb_num ||
        sl->first_mb_addr >= h->mb_num) {
        av_log(h->avctx, AV_LOG_ERROR, "first_mb_in_slice overflow\n");
        return AVERROR_INVALIDDATA;
    }
    sl->resync_mb_x = sl->mb_x =  sl->first_mb_addr % h->mb_width;
    sl->resync_mb_y = sl->mb_y = (sl->first_mb_addr / h->mb_width) <<
                                 FIELD_OR_MBAFF_PICTURE(h);
    if (h->picture_structure == PICT_BOTTOM_FIELD)
        sl->resync_mb_y = sl->mb_y = sl->mb_y + 1;
    av_assert1(sl->mb_y < h->mb_height);

    ret = ff_h264_build_ref_list(h, sl);
    if (ret < 0)
        return ret;

    if (h->ps.pps->weighted_bipred_idc == 2 &&
        sl->slice_type_nos == AV_PICTURE_TYPE_B) {
        implicit_weight_table(h, sl, -1);
        if (FRAME_MBAFF(h)) {
            implicit_weight_table(h, sl, 0);
            implicit_weight_table(h, sl, 1);
        }
    }

    if (sl->slice_type_nos == AV_PICTURE_TYPE_B && !sl->direct_spatial_mv_pred)
        ff_h264_direct_dist_scale_factor(h, sl);
    if (!h->setup_finished)
        ff_h264_direct_ref_list_init(h, sl);

    if (h->avctx->skip_loop_filter >= AVDISCARD_ALL ||
        (h->avctx->skip_loop_filter >= AVDISCARD_NONKEY &&
         h->nal_unit_type != H264_NAL_IDR_SLICE) ||
        (h->avctx->skip_loop_filter >= AVDISCARD_NONINTRA &&
         sl->slice_type_nos != AV_PICTURE_TYPE_I) ||
        (h->avctx->skip_loop_filter >= AVDISCARD_BIDIR  &&
         sl->slice_type_nos == AV_PICTURE_TYPE_B) ||
        (h->avctx->skip_loop_filter >= AVDISCARD_NONREF &&
         nal->ref_idc == 0))
        sl->deblocking_filter = 0;

    if (sl->deblocking_filter == 1 && h->nb_slice_ctx > 1) {
        if (h->avctx->flags2 & AV_CODEC_FLAG2_FAST) {
            /* Cheat slightly for speed:
             * Do not bother to deblock across slices. */
            sl->deblocking_filter = 2;
        } else {
            h->postpone_filter = 1;
        }
    }
    sl->qp_thresh = 15 -
                   FFMIN(sl->slice_alpha_c0_offset, sl->slice_beta_offset) -
                   FFMAX3(0,
                          h->ps.pps->chroma_qp_index_offset[0],
                          h->ps.pps->chroma_qp_index_offset[1]) +
                   6 * (h->ps.sps->bit_depth_luma - 8);

    sl->slice_num       = ++h->current_slice;

    if (sl->slice_num)
        h->slice_row[(sl->slice_num-1)&(MAX_SLICES-1)]= sl->resync_mb_y;
    if (   h->slice_row[sl->slice_num&(MAX_SLICES-1)] + 3 >= sl->resync_mb_y
        && h->slice_row[sl->slice_num&(MAX_SLICES-1)] <= sl->resync_mb_y
        && sl->slice_num >= MAX_SLICES) {
        //in case of ASO this check needs to be updated depending on how we decide to assign slice numbers in this case
        av_log(h->avctx, AV_LOG_WARNING, "Possibly too many slices (%d >= %d), increase MAX_SLICES and recompile if there are artifacts\n", sl->slice_num, MAX_SLICES);
    }

    for (j = 0; j < 2; j++) {
        int id_list[16];
        int *ref2frm = h->ref2frm[sl->slice_num & (MAX_SLICES - 1)][j];
        for (i = 0; i < 16; i++) {
            id_list[i] = 60;
            if (j < sl->list_count && i < sl->ref_count[j] &&
                sl->ref_list[j][i].parent->f->buf[0]) {
                int k;
                AVBuffer *buf = sl->ref_list[j][i].parent->f->buf[0]->buffer;
                for (k = 0; k < h->short_ref_count; k++)
                    if (h->short_ref[k]->f->buf[0]->buffer == buf) {
                        id_list[i] = k;
                        break;
                    }
                for (k = 0; k < h->long_ref_count; k++)
                    if (h->long_ref[k] && h->long_ref[k]->f->buf[0]->buffer == buf) {
                        id_list[i] = h->short_ref_count + k;
                        break;
                    }
            }
        }

        ref2frm[0] =
        ref2frm[1] = -1;
        for (i = 0; i < 16; i++)
            ref2frm[i + 2] = 4 * id_list[i] + (sl->ref_list[j][i].reference & 3);
        ref2frm[18 + 0] =
        ref2frm[18 + 1] = -1;
        for (i = 16; i < 48; i++)
            ref2frm[i + 4] = 4 * id_list[(i - 16) >> 1] +
                             (sl->ref_list[j][i].reference & 3);
    }

    if (h->avctx->debug & FF_DEBUG_PICT_INFO) {
        av_log(h->avctx, AV_LOG_DEBUG,
               "slice:%d %s mb:%d %c%s%s frame:%d poc:%d/%d ref:%d/%d qp:%d loop:%d:%d:%d weight:%d%s %s\n",
               sl->slice_num,
               (h->picture_structure == PICT_FRAME ? "F" : h->picture_structure == PICT_TOP_FIELD ? "T" : "B"),
               sl->mb_y * h->mb_width + sl->mb_x,
               av_get_picture_type_char(sl->slice_type),
               sl->slice_type_fixed ? " fix" : "",
               nal->type == H264_NAL_IDR_SLICE ? " IDR" : "",
               h->poc.frame_num,
               h->cur_pic_ptr->field_poc[0],
               h->cur_pic_ptr->field_poc[1],
               sl->ref_count[0], sl->ref_count[1],
               sl->qscale,
               sl->deblocking_filter,
               sl->slice_alpha_c0_offset, sl->slice_beta_offset,
               sl->pwt.use_weight,
               sl->pwt.use_weight == 1 && sl->pwt.use_weight_chroma ? "c" : "",
               sl->slice_type == AV_PICTURE_TYPE_B ? (sl->direct_spatial_mv_pred ? "SPAT" : "TEMP") : "");
    }

    return 0;
}