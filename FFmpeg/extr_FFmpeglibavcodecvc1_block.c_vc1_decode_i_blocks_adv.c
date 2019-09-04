#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_20__ {int* qscale_table; scalar_t__*** motion_val; int /*<<< orphan*/ * mb_type; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* clear_blocks ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_23__ {int mb_x; int mb_y; int mb_intra; int first_slice_line; int start_mb_y; size_t* block_index; int b8_stride; int end_mb_y; int mb_width; int mb_stride; int /*<<< orphan*/  er; scalar_t__ loop_filter; int /*<<< orphan*/  gb; TYPE_16__* avctx; int /*<<< orphan*/ * c_dc_scale_table; int /*<<< orphan*/  c_dc_scale; int /*<<< orphan*/ * y_dc_scale_table; int /*<<< orphan*/  y_dc_scale; TYPE_2__ current_picture; void* ac_pred; TYPE_1__ bdsp; int /*<<< orphan*/ * coded_block; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* vc1_inv_trans_8x8 ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_22__ {int y_ac_table_index; int pqindex; int c_ac_table_index; int pq; size_t cur_blk_idx; int mb_off; size_t blocks_off; scalar_t__ condover; int** mb_type; int a_avail; int c_avail; size_t topleft_blk_idx; size_t top_blk_idx; size_t left_blk_idx; int field_mode; TYPE_5__ s; int /*<<< orphan*/  bits; scalar_t__ overlap; int /*<<< orphan*/ ** block; TYPE_3__ vc1dsp; int /*<<< orphan*/  codingset2; int /*<<< orphan*/  codingset; void** over_flags_plane; scalar_t__ overflg_is_raw; void** acpred_plane; scalar_t__ acpred_is_raw; void** fieldtx_plane; scalar_t__ fieldtx_is_raw; } ;
typedef  TYPE_4__ VC1Context ;
struct TYPE_18__ {int flags; } ;
struct TYPE_17__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_5__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ CONDOVER_NONE ; 
 scalar_t__ CONDOVER_SELECT ; 
 scalar_t__ CONFIG_GRAY ; 
 int /*<<< orphan*/  CS_HIGH_MOT_INTER ; 
 int /*<<< orphan*/  CS_HIGH_MOT_INTRA ; 
 int /*<<< orphan*/  CS_HIGH_RATE_INTER ; 
 int /*<<< orphan*/  CS_HIGH_RATE_INTRA ; 
 int /*<<< orphan*/  CS_LOW_MOT_INTER ; 
 int /*<<< orphan*/  CS_LOW_MOT_INTRA ; 
 int /*<<< orphan*/  CS_MID_RATE_INTER ; 
 int /*<<< orphan*/  CS_MID_RATE_INTRA ; 
 int /*<<< orphan*/  ER_MB_END ; 
 int /*<<< orphan*/  ER_MB_ERROR ; 
 size_t FFABS (int) ; 
 int /*<<< orphan*/  GET_MQUANT () ; 
 int /*<<< orphan*/  MB_INTRA_VLC_BITS ; 
 int /*<<< orphan*/  MB_TYPE_INTRA ; 
 int /*<<< orphan*/  av_log (TYPE_16__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t* block_map ; 
 int /*<<< orphan*/  ff_er_add_slice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mpeg_draw_horiz_band (TYPE_5__*,int,int) ; 
 TYPE_14__ ff_msmp4_mb_i_vlc ; 
 int /*<<< orphan*/  ff_update_block_index (TYPE_5__*) ; 
 int /*<<< orphan*/  ff_vc1_i_loop_filter (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_vc1_i_overlap_filter (TYPE_4__*) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits_count (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inc_blk_idx (size_t) ; 
 int /*<<< orphan*/  init_block_index (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int vc1_coded_block_pred (TYPE_5__*,int,int**) ; 
 int /*<<< orphan*/  vc1_decode_i_block_adv (TYPE_4__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vc1_put_blocks_clamped (TYPE_4__*,int) ; 

__attribute__((used)) static void vc1_decode_i_blocks_adv(VC1Context *v)
{
    int k;
    MpegEncContext *s = &v->s;
    int cbp, val;
    uint8_t *coded_val;
    int mb_pos;
    int mquant;
    int mqdiff;
    GetBitContext *gb = &s->gb;

    /* select coding mode used for VLC tables selection */
    switch (v->y_ac_table_index) {
    case 0:
        v->codingset = (v->pqindex <= 8) ? CS_HIGH_RATE_INTRA : CS_LOW_MOT_INTRA;
        break;
    case 1:
        v->codingset = CS_HIGH_MOT_INTRA;
        break;
    case 2:
        v->codingset = CS_MID_RATE_INTRA;
        break;
    }

    switch (v->c_ac_table_index) {
    case 0:
        v->codingset2 = (v->pqindex <= 8) ? CS_HIGH_RATE_INTER : CS_LOW_MOT_INTER;
        break;
    case 1:
        v->codingset2 = CS_HIGH_MOT_INTER;
        break;
    case 2:
        v->codingset2 = CS_MID_RATE_INTER;
        break;
    }

    // do frame decode
    s->mb_x             = s->mb_y = 0;
    s->mb_intra         = 1;
    s->first_slice_line = 1;
    s->mb_y             = s->start_mb_y;
    if (s->start_mb_y) {
        s->mb_x = 0;
        init_block_index(v);
        memset(&s->coded_block[s->block_index[0] - s->b8_stride], 0,
               (1 + s->b8_stride) * sizeof(*s->coded_block));
    }
    for (; s->mb_y < s->end_mb_y; s->mb_y++) {
        s->mb_x = 0;
        init_block_index(v);
        for (;s->mb_x < s->mb_width; s->mb_x++) {
            mquant = v->pq;
            ff_update_block_index(s);
            s->bdsp.clear_blocks(v->block[v->cur_blk_idx][0]);
            mb_pos = s->mb_x + s->mb_y * s->mb_stride;
            s->current_picture.mb_type[mb_pos + v->mb_off]                         = MB_TYPE_INTRA;
            for (int i = 0; i < 4; i++) {
                s->current_picture.motion_val[1][s->block_index[i] + v->blocks_off][0] = 0;
                s->current_picture.motion_val[1][s->block_index[i] + v->blocks_off][1] = 0;
            }

            // do actual MB decoding and displaying
            if (v->fieldtx_is_raw)
                v->fieldtx_plane[mb_pos] = get_bits1(&v->s.gb);
            cbp = get_vlc2(&v->s.gb, ff_msmp4_mb_i_vlc.table, MB_INTRA_VLC_BITS, 2);
            if (v->acpred_is_raw)
                v->s.ac_pred = get_bits1(&v->s.gb);
            else
                v->s.ac_pred = v->acpred_plane[mb_pos];

            if (v->condover == CONDOVER_SELECT && v->overflg_is_raw)
                v->over_flags_plane[mb_pos] = get_bits1(&v->s.gb);

            GET_MQUANT();

            s->current_picture.qscale_table[mb_pos] = mquant;
            /* Set DC scale - y and c use the same */
            s->y_dc_scale = s->y_dc_scale_table[FFABS(mquant)];
            s->c_dc_scale = s->c_dc_scale_table[FFABS(mquant)];

            for (k = 0; k < 6; k++) {
                v->mb_type[0][s->block_index[k]] = 1;

                val = ((cbp >> (5 - k)) & 1);

                if (k < 4) {
                    int pred   = vc1_coded_block_pred(&v->s, k, &coded_val);
                    val        = val ^ pred;
                    *coded_val = val;
                }
                cbp |= val << (5 - k);

                v->a_avail = !s->first_slice_line || (k == 2 || k == 3);
                v->c_avail = !!s->mb_x || (k == 1 || k == 3);

                vc1_decode_i_block_adv(v, v->block[v->cur_blk_idx][block_map[k]], k, val,
                                       (k < 4) ? v->codingset : v->codingset2, mquant);

                if (CONFIG_GRAY && k > 3 && (s->avctx->flags & AV_CODEC_FLAG_GRAY))
                    continue;
                v->vc1dsp.vc1_inv_trans_8x8(v->block[v->cur_blk_idx][block_map[k]]);
            }

            if (v->overlap && (v->pq >= 9 || v->condover != CONDOVER_NONE))
                ff_vc1_i_overlap_filter(v);
            vc1_put_blocks_clamped(v, 1);
            if (v->s.loop_filter)
                ff_vc1_i_loop_filter(v);

            if (get_bits_count(&s->gb) > v->bits) {
                // TODO: may need modification to handle slice coding
                ff_er_add_slice(&s->er, 0, s->start_mb_y, s->mb_x, s->mb_y, ER_MB_ERROR);
                av_log(s->avctx, AV_LOG_ERROR, "Bits overconsumption: %i > %i\n",
                       get_bits_count(&s->gb), v->bits);
                return;
            }
            inc_blk_idx(v->topleft_blk_idx);
            inc_blk_idx(v->top_blk_idx);
            inc_blk_idx(v->left_blk_idx);
            inc_blk_idx(v->cur_blk_idx);
        }
        if (!v->s.loop_filter)
            ff_mpeg_draw_horiz_band(s, s->mb_y * 16, 16);
        else if (s->mb_y)
            ff_mpeg_draw_horiz_band(s, (s->mb_y-1) * 16, 16);
        s->first_slice_line = 0;
    }

    if (v->s.loop_filter)
        ff_mpeg_draw_horiz_band(s, (s->end_mb_y - 1) * 16, 16);
    ff_er_add_slice(&s->er, 0, s->start_mb_y << v->field_mode, s->mb_width - 1,
                    (s->end_mb_y << v->field_mode) - 1, ER_MB_END);
}