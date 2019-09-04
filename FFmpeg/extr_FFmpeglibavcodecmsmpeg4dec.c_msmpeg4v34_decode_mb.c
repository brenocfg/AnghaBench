#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_18__ {int /*<<< orphan*/  table; } ;
struct TYPE_17__ {int /*<<< orphan*/  table; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* clear_blocks ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {int* mb_type; } ;
struct TYPE_16__ {size_t mb_x; size_t mb_y; size_t mb_stride; scalar_t__ pict_type; int mb_intra; int* block_last_index; int*** mv; int mb_skipped; size_t ac_pred; size_t h263_aic_dir; int /*<<< orphan*/  avctx; int /*<<< orphan*/ * block; TYPE_1__ bdsp; void* rl_table_index; void* rl_chroma_table_index; int /*<<< orphan*/  gb; scalar_t__ per_mb_rl_table; scalar_t__ inter_intra_pred; void* mv_type; void* mv_dir; scalar_t__ use_skip_mb_code; TYPE_2__ current_picture; } ;
struct TYPE_13__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_P ; 
 size_t DEFAULT_INTER_INDEX ; 
 int /*<<< orphan*/  INTER_INTRA_VLC_BITS ; 
 int /*<<< orphan*/  MB_INTRA_VLC_BITS ; 
 int /*<<< orphan*/  MB_NON_INTRA_VLC_BITS ; 
 int MB_TYPE_16x16 ; 
 int MB_TYPE_INTRA ; 
 int MB_TYPE_L0 ; 
 int MB_TYPE_SKIP ; 
 void* MV_DIR_FORWARD ; 
 void* MV_TYPE_16X16 ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,size_t,int) ; 
 void* decode012 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_3__*,char*,size_t,size_t,int,size_t) ; 
 int /*<<< orphan*/  ff_h263_pred_motion (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_10__ ff_inter_intra_vlc ; 
 TYPE_9__* ff_mb_non_intra_vlc ; 
 TYPE_8__ ff_msmp4_mb_i_vlc ; 
 int ff_msmpeg4_coded_block_pred (TYPE_3__*,int,int**) ; 
 scalar_t__ ff_msmpeg4_decode_block (TYPE_3__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_msmpeg4_decode_motion (TYPE_3__*,int*,int*) ; 
 size_t get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 void* get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msmpeg4v34_decode_mb(MpegEncContext *s, int16_t block[6][64])
{
    int cbp, code, i;
    uint8_t *coded_val;
    uint32_t * const mb_type_ptr = &s->current_picture.mb_type[s->mb_x + s->mb_y*s->mb_stride];

    if (get_bits_left(&s->gb) <= 0)
        return AVERROR_INVALIDDATA;

    if (s->pict_type == AV_PICTURE_TYPE_P) {
        if (s->use_skip_mb_code) {
            if (get_bits1(&s->gb)) {
                /* skip mb */
                s->mb_intra = 0;
                for(i=0;i<6;i++)
                    s->block_last_index[i] = -1;
                s->mv_dir = MV_DIR_FORWARD;
                s->mv_type = MV_TYPE_16X16;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->mb_skipped = 1;
                *mb_type_ptr = MB_TYPE_SKIP | MB_TYPE_L0 | MB_TYPE_16x16;

                return 0;
            }
        }

        code = get_vlc2(&s->gb, ff_mb_non_intra_vlc[DEFAULT_INTER_INDEX].table, MB_NON_INTRA_VLC_BITS, 3);
        if (code < 0)
            return -1;
        //s->mb_intra = (code & 0x40) ? 0 : 1;
        s->mb_intra = (~code & 0x40) >> 6;

        cbp = code & 0x3f;
    } else {
        s->mb_intra = 1;
        code = get_vlc2(&s->gb, ff_msmp4_mb_i_vlc.table, MB_INTRA_VLC_BITS, 2);
        if (code < 0)
            return -1;
        /* predict coded block pattern */
        cbp = 0;
        for(i=0;i<6;i++) {
            int val = ((code >> (5 - i)) & 1);
            if (i < 4) {
                int pred = ff_msmpeg4_coded_block_pred(s, i, &coded_val);
                val = val ^ pred;
                *coded_val = val;
            }
            cbp |= val << (5 - i);
        }
    }

    if (!s->mb_intra) {
        int mx, my;
        if(s->per_mb_rl_table && cbp){
            s->rl_table_index = decode012(&s->gb);
            s->rl_chroma_table_index = s->rl_table_index;
        }
        ff_h263_pred_motion(s, 0, 0, &mx, &my);
        if (ff_msmpeg4_decode_motion(s, &mx, &my) < 0)
            return -1;
        s->mv_dir = MV_DIR_FORWARD;
        s->mv_type = MV_TYPE_16X16;
        s->mv[0][0][0] = mx;
        s->mv[0][0][1] = my;
        *mb_type_ptr = MB_TYPE_L0 | MB_TYPE_16x16;
    } else {
        ff_dlog(s, "I at %d %d %d %06X\n", s->mb_x, s->mb_y,
                ((cbp & 3) ? 1 : 0) +((cbp & 0x3C)? 2 : 0),
                show_bits(&s->gb, 24));
        s->ac_pred = get_bits1(&s->gb);
        *mb_type_ptr = MB_TYPE_INTRA;
        if(s->inter_intra_pred){
            s->h263_aic_dir= get_vlc2(&s->gb, ff_inter_intra_vlc.table, INTER_INTRA_VLC_BITS, 1);
            ff_dlog(s, "%d%d %d %d/",
                    s->ac_pred, s->h263_aic_dir, s->mb_x, s->mb_y);
        }
        if(s->per_mb_rl_table && cbp){
            s->rl_table_index = decode012(&s->gb);
            s->rl_chroma_table_index = s->rl_table_index;
        }
    }

    s->bdsp.clear_blocks(s->block[0]);
    for (i = 0; i < 6; i++) {
        if (ff_msmpeg4_decode_block(s, block[i], i, (cbp >> (5 - i)) & 1, NULL) < 0)
        {
            av_log(s->avctx, AV_LOG_ERROR, "\nerror while decoding block: %d x %d (%d)\n", s->mb_x, s->mb_y, i);
            return -1;
        }
    }

    return 0;
}