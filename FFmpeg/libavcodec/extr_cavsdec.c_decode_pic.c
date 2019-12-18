#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  enum cavs_mb { ____Placeholder_cavs_mb } cavs_mb ;
struct TYPE_15__ {scalar_t__ pict_type; int* linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int poc; TYPE_2__* f; } ;
struct TYPE_14__ {scalar_t__ stc; int stream_revision; int* dist; int* scale_den; int sym_factor; int* direct_den; int progressive; int pic_structure; int pic_qp_fixed; int qp_fixed; int qp; int ref_flag; int skip_mode_flag; int loop_filter_disable; int alpha_offset; int beta_offset; TYPE_11__* DPB; TYPE_11__ cur; int /*<<< orphan*/  gb; scalar_t__ low_delay; int /*<<< orphan*/  avctx; int /*<<< orphan*/  edge_emu_buffer; int /*<<< orphan*/  top_qp; } ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVSFrame ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PICTURE_TYPE_P ; 
 int B_8X8 ; 
 int B_SKIP ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFABS (int) ; 
 int FFALIGN (int,int) ; 
 int /*<<< orphan*/  FFSWAP (int /*<<< orphan*/ ,TYPE_11__,TYPE_11__) ; 
 scalar_t__ PIC_PB_START_CODE ; 
 int P_8X8 ; 
 int P_SKIP ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_mallocz (int) ; 
 scalar_t__ check_for_slice (TYPE_1__*) ; 
 int decode_mb_b (TYPE_1__*,int) ; 
 int decode_mb_i (TYPE_1__*,int) ; 
 int /*<<< orphan*/  decode_mb_p (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emms_c () ; 
 int ff_cavs_init_pic (TYPE_1__*) ; 
 scalar_t__ ff_cavs_next_mb (TYPE_1__*) ; 
 int ff_get_buffer (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 void* get_se_golomb (int /*<<< orphan*/ *) ; 
 int get_ue_golomb (int /*<<< orphan*/ *) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_pic(AVSContext *h)
{
    int ret;
    int skip_count    = -1;
    enum cavs_mb mb_type;

    if (!h->top_qp) {
        av_log(h->avctx, AV_LOG_ERROR, "No sequence header decoded yet\n");
        return AVERROR_INVALIDDATA;
    }

    av_frame_unref(h->cur.f);

    skip_bits(&h->gb, 16);//bbv_dwlay
    if (h->stc == PIC_PB_START_CODE) {
        h->cur.f->pict_type = get_bits(&h->gb, 2) + AV_PICTURE_TYPE_I;
        if (h->cur.f->pict_type > AV_PICTURE_TYPE_B) {
            av_log(h->avctx, AV_LOG_ERROR, "illegal picture type\n");
            return AVERROR_INVALIDDATA;
        }
        /* make sure we have the reference frames we need */
        if (!h->DPB[0].f->data[0] ||
           (!h->DPB[1].f->data[0] && h->cur.f->pict_type == AV_PICTURE_TYPE_B))
            return AVERROR_INVALIDDATA;
    } else {
        h->cur.f->pict_type = AV_PICTURE_TYPE_I;
        if (get_bits1(&h->gb))
            skip_bits(&h->gb, 24);//time_code
        /* old sample clips were all progressive and no low_delay,
           bump stream revision if detected otherwise */
        if (h->low_delay || !(show_bits(&h->gb, 9) & 1))
            h->stream_revision = 1;
        /* similarly test top_field_first and repeat_first_field */
        else if (show_bits(&h->gb, 11) & 3)
            h->stream_revision = 1;
        if (h->stream_revision > 0)
            skip_bits(&h->gb, 1); //marker_bit
    }

    ret = ff_get_buffer(h->avctx, h->cur.f, h->cur.f->pict_type == AV_PICTURE_TYPE_B ?
                        0 : AV_GET_BUFFER_FLAG_REF);
    if (ret < 0)
        return ret;

    if (!h->edge_emu_buffer) {
        int alloc_size = FFALIGN(FFABS(h->cur.f->linesize[0]) + 32, 32);
        h->edge_emu_buffer = av_mallocz(alloc_size * 2 * 24);
        if (!h->edge_emu_buffer)
            return AVERROR(ENOMEM);
    }

    if ((ret = ff_cavs_init_pic(h)) < 0)
        return ret;
    h->cur.poc = get_bits(&h->gb, 8) * 2;

    /* get temporal distances and MV scaling factors */
    if (h->cur.f->pict_type != AV_PICTURE_TYPE_B) {
        h->dist[0] = (h->cur.poc - h->DPB[0].poc) & 511;
    } else {
        h->dist[0] = (h->DPB[0].poc  - h->cur.poc) & 511;
    }
    h->dist[1] = (h->cur.poc - h->DPB[1].poc) & 511;
    h->scale_den[0] = h->dist[0] ? 512/h->dist[0] : 0;
    h->scale_den[1] = h->dist[1] ? 512/h->dist[1] : 0;
    if (h->cur.f->pict_type == AV_PICTURE_TYPE_B) {
        h->sym_factor = h->dist[0] * h->scale_den[1];
        if (FFABS(h->sym_factor) > 32768) {
            av_log(h->avctx, AV_LOG_ERROR, "sym_factor %d too large\n", h->sym_factor);
            return AVERROR_INVALIDDATA;
        }
    } else {
        h->direct_den[0] = h->dist[0] ? 16384 / h->dist[0] : 0;
        h->direct_den[1] = h->dist[1] ? 16384 / h->dist[1] : 0;
    }

    if (h->low_delay)
        get_ue_golomb(&h->gb); //bbv_check_times
    h->progressive   = get_bits1(&h->gb);
    h->pic_structure = 1;
    if (!h->progressive)
        h->pic_structure = get_bits1(&h->gb);
    if (!h->pic_structure && h->stc == PIC_PB_START_CODE)
        skip_bits1(&h->gb);     //advanced_pred_mode_disable
    skip_bits1(&h->gb);        //top_field_first
    skip_bits1(&h->gb);        //repeat_first_field
    h->pic_qp_fixed =
    h->qp_fixed = get_bits1(&h->gb);
    h->qp       = get_bits(&h->gb, 6);
    if (h->cur.f->pict_type == AV_PICTURE_TYPE_I) {
        if (!h->progressive && !h->pic_structure)
            skip_bits1(&h->gb);//what is this?
        skip_bits(&h->gb, 4);   //reserved bits
    } else {
        if (!(h->cur.f->pict_type == AV_PICTURE_TYPE_B && h->pic_structure == 1))
            h->ref_flag        = get_bits1(&h->gb);
        skip_bits(&h->gb, 4);   //reserved bits
        h->skip_mode_flag      = get_bits1(&h->gb);
    }
    h->loop_filter_disable     = get_bits1(&h->gb);
    if (!h->loop_filter_disable && get_bits1(&h->gb)) {
        h->alpha_offset        = get_se_golomb(&h->gb);
        h->beta_offset         = get_se_golomb(&h->gb);
        if (   h->alpha_offset < -64 || h->alpha_offset > 64
            || h-> beta_offset < -64 || h-> beta_offset > 64) {
            h->alpha_offset = h->beta_offset  = 0;
            return AVERROR_INVALIDDATA;
        }
    } else {
        h->alpha_offset = h->beta_offset  = 0;
    }

    ret = 0;
    if (h->cur.f->pict_type == AV_PICTURE_TYPE_I) {
        do {
            check_for_slice(h);
            ret = decode_mb_i(h, 0);
            if (ret < 0)
                break;
        } while (ff_cavs_next_mb(h));
    } else if (h->cur.f->pict_type == AV_PICTURE_TYPE_P) {
        do {
            if (check_for_slice(h))
                skip_count = -1;
            if (h->skip_mode_flag && (skip_count < 0)) {
                if (get_bits_left(&h->gb) < 1) {
                    ret = AVERROR_INVALIDDATA;
                    break;
                }
                skip_count = get_ue_golomb(&h->gb);
            }
            if (h->skip_mode_flag && skip_count--) {
                decode_mb_p(h, P_SKIP);
            } else {
                if (get_bits_left(&h->gb) < 1) {
                    ret = AVERROR_INVALIDDATA;
                    break;
                }
                mb_type = get_ue_golomb(&h->gb) + P_SKIP + h->skip_mode_flag;
                if (mb_type > P_8X8)
                    ret = decode_mb_i(h, mb_type - P_8X8 - 1);
                else
                    decode_mb_p(h, mb_type);
            }
            if (ret < 0)
                break;
        } while (ff_cavs_next_mb(h));
    } else { /* AV_PICTURE_TYPE_B */
        do {
            if (check_for_slice(h))
                skip_count = -1;
            if (h->skip_mode_flag && (skip_count < 0)) {
                if (get_bits_left(&h->gb) < 1) {
                    ret = AVERROR_INVALIDDATA;
                    break;
                }
                skip_count = get_ue_golomb(&h->gb);
            }
            if (h->skip_mode_flag && skip_count--) {
                ret = decode_mb_b(h, B_SKIP);
            } else {
                if (get_bits_left(&h->gb) < 1) {
                    ret = AVERROR_INVALIDDATA;
                    break;
                }
                mb_type = get_ue_golomb(&h->gb) + B_SKIP + h->skip_mode_flag;
                if (mb_type > B_8X8)
                    ret = decode_mb_i(h, mb_type - B_8X8 - 1);
                else
                    ret = decode_mb_b(h, mb_type);
            }
            if (ret < 0)
                break;
        } while (ff_cavs_next_mb(h));
    }
    emms_c();
    if (ret >= 0 && h->cur.f->pict_type != AV_PICTURE_TYPE_B) {
        av_frame_unref(h->DPB[1].f);
        FFSWAP(AVSFrame, h->cur, h->DPB[1]);
        FFSWAP(AVSFrame, h->DPB[0], h->DPB[1]);
    }
    return ret;
}