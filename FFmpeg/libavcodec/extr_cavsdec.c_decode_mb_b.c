#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  enum cavs_sub_mb { ____Placeholder_cavs_sub_mb } cavs_sub_mb ;
typedef  enum cavs_mb { ____Placeholder_cavs_mb } cavs_mb ;
struct TYPE_11__ {size_t mbidx; void** mv; int /*<<< orphan*/  avctx; int /*<<< orphan*/ * col_mv; int /*<<< orphan*/ * col_type_base; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  BLK_16X16 ; 
 int /*<<< orphan*/  BLK_16X8 ; 
 int /*<<< orphan*/  BLK_8X16 ; 
 int /*<<< orphan*/  BLK_8X8 ; 
 int BWD0 ; 
 int BWD1 ; 
#define  B_8X8 136 
#define  B_BWD_16X16 135 
#define  B_DIRECT 134 
#define  B_FWD_16X16 133 
#define  B_SKIP 132 
 int B_SUB_BWD ; 
#define  B_SUB_DIRECT 131 
#define  B_SUB_FWD 130 
#define  B_SUB_SYM 129 
#define  B_SYM_16X16 128 
 int FWD0 ; 
 int FWD1 ; 
 size_t MV_BWD_A1 ; 
 size_t MV_BWD_B3 ; 
 size_t MV_BWD_C2 ; 
 size_t MV_BWD_OFFS ; 
 size_t MV_BWD_X0 ; 
 size_t MV_BWD_X1 ; 
 size_t MV_BWD_X2 ; 
 size_t MV_FWD_A1 ; 
 size_t MV_FWD_B3 ; 
 size_t MV_FWD_C2 ; 
 size_t MV_FWD_X0 ; 
 size_t MV_FWD_X1 ; 
 size_t MV_FWD_X2 ; 
 int /*<<< orphan*/  MV_PRED_BSKIP ; 
 int /*<<< orphan*/  MV_PRED_LEFT ; 
 int /*<<< orphan*/  MV_PRED_MEDIAN ; 
 int /*<<< orphan*/  MV_PRED_TOP ; 
 int /*<<< orphan*/  MV_PRED_TOPRIGHT ; 
 int SYM0 ; 
 int SYM1 ; 
 size_t TMP_UNUSED_INX ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  decode_residual_inter (TYPE_1__*) ; 
 void* ff_cavs_dir_mv ; 
 int /*<<< orphan*/  ff_cavs_filter (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_cavs_init_mb (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_cavs_inter (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_cavs_mv (TYPE_1__*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* ff_cavs_partition_flags ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mv_pred_direct (TYPE_1__*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_pred_sym (TYPE_1__*,void**,int /*<<< orphan*/ ) ; 
 size_t* mv_scan ; 
 int /*<<< orphan*/  set_intra_mode_default (TYPE_1__*) ; 
 int /*<<< orphan*/  set_mvs (void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_mb_b(AVSContext *h, enum cavs_mb mb_type)
{
    int block;
    enum cavs_sub_mb sub_type[4];
    int flags;

    ff_cavs_init_mb(h);

    /* reset all MVs */
    h->mv[MV_FWD_X0] = ff_cavs_dir_mv;
    set_mvs(&h->mv[MV_FWD_X0], BLK_16X16);
    h->mv[MV_BWD_X0] = ff_cavs_dir_mv;
    set_mvs(&h->mv[MV_BWD_X0], BLK_16X16);
    switch (mb_type) {
    case B_SKIP:
    case B_DIRECT:
        if (!h->col_type_base[h->mbidx]) {
            /* intra MB at co-location, do in-plane prediction */
            ff_cavs_mv(h, MV_FWD_X0, MV_FWD_C2, MV_PRED_BSKIP, BLK_16X16, 1);
            ff_cavs_mv(h, MV_BWD_X0, MV_BWD_C2, MV_PRED_BSKIP, BLK_16X16, 0);
        } else
            /* direct prediction from co-located P MB, block-wise */
            for (block = 0; block < 4; block++)
                mv_pred_direct(h, &h->mv[mv_scan[block]],
                               &h->col_mv[h->mbidx * 4 + block]);
        break;
    case B_FWD_16X16:
        ff_cavs_mv(h, MV_FWD_X0, MV_FWD_C2, MV_PRED_MEDIAN, BLK_16X16, 1);
        break;
    case B_SYM_16X16:
        ff_cavs_mv(h, MV_FWD_X0, MV_FWD_C2, MV_PRED_MEDIAN, BLK_16X16, 1);
        mv_pred_sym(h, &h->mv[MV_FWD_X0], BLK_16X16);
        break;
    case B_BWD_16X16:
        ff_cavs_mv(h, MV_BWD_X0, MV_BWD_C2, MV_PRED_MEDIAN, BLK_16X16, 0);
        break;
    case B_8X8:
#define TMP_UNUSED_INX  7
        flags = 0;
        for (block = 0; block < 4; block++)
            sub_type[block] = get_bits(&h->gb, 2);
        for (block = 0; block < 4; block++) {
            switch (sub_type[block]) {
            case B_SUB_DIRECT:
                if (!h->col_type_base[h->mbidx]) {
                    /* intra MB at co-location, do in-plane prediction */
                    if(flags==0) {
                        // if col-MB is a Intra MB, current Block size is 16x16.
                        // AVS standard section 9.9.1
                        if(block>0){
                            h->mv[TMP_UNUSED_INX              ] = h->mv[MV_FWD_X0              ];
                            h->mv[TMP_UNUSED_INX + MV_BWD_OFFS] = h->mv[MV_FWD_X0 + MV_BWD_OFFS];
                        }
                        ff_cavs_mv(h, MV_FWD_X0, MV_FWD_C2,
                                   MV_PRED_BSKIP, BLK_8X8, 1);
                        ff_cavs_mv(h, MV_FWD_X0+MV_BWD_OFFS,
                                   MV_FWD_C2+MV_BWD_OFFS,
                                   MV_PRED_BSKIP, BLK_8X8, 0);
                        if(block>0) {
                            flags = mv_scan[block];
                            h->mv[flags              ] = h->mv[MV_FWD_X0              ];
                            h->mv[flags + MV_BWD_OFFS] = h->mv[MV_FWD_X0 + MV_BWD_OFFS];
                            h->mv[MV_FWD_X0              ] = h->mv[TMP_UNUSED_INX              ];
                            h->mv[MV_FWD_X0 + MV_BWD_OFFS] = h->mv[TMP_UNUSED_INX + MV_BWD_OFFS];
                        } else
                            flags = MV_FWD_X0;
                    } else {
                        h->mv[mv_scan[block]              ] = h->mv[flags              ];
                        h->mv[mv_scan[block] + MV_BWD_OFFS] = h->mv[flags + MV_BWD_OFFS];
                    }
                } else
                    mv_pred_direct(h, &h->mv[mv_scan[block]],
                                   &h->col_mv[h->mbidx * 4 + block]);
                break;
            case B_SUB_FWD:
                ff_cavs_mv(h, mv_scan[block], mv_scan[block] - 3,
                           MV_PRED_MEDIAN, BLK_8X8, 1);
                break;
            case B_SUB_SYM:
                ff_cavs_mv(h, mv_scan[block], mv_scan[block] - 3,
                           MV_PRED_MEDIAN, BLK_8X8, 1);
                mv_pred_sym(h, &h->mv[mv_scan[block]], BLK_8X8);
                break;
            }
        }
#undef TMP_UNUSED_INX
        for (block = 0; block < 4; block++) {
            if (sub_type[block] == B_SUB_BWD)
                ff_cavs_mv(h, mv_scan[block] + MV_BWD_OFFS,
                           mv_scan[block] + MV_BWD_OFFS - 3,
                           MV_PRED_MEDIAN, BLK_8X8, 0);
        }
        break;
    default:
        if (mb_type <= B_SYM_16X16) {
            av_log(h->avctx, AV_LOG_ERROR, "Invalid mb_type %d in B frame\n", mb_type);
            return AVERROR_INVALIDDATA;
        }
        av_assert2(mb_type < B_8X8);
        flags = ff_cavs_partition_flags[mb_type];
        if (mb_type & 1) { /* 16x8 macroblock types */
            if (flags & FWD0)
                ff_cavs_mv(h, MV_FWD_X0, MV_FWD_C2, MV_PRED_TOP,  BLK_16X8, 1);
            if (flags & SYM0)
                mv_pred_sym(h, &h->mv[MV_FWD_X0], BLK_16X8);
            if (flags & FWD1)
                ff_cavs_mv(h, MV_FWD_X2, MV_FWD_A1, MV_PRED_LEFT, BLK_16X8, 1);
            if (flags & SYM1)
                mv_pred_sym(h, &h->mv[MV_FWD_X2], BLK_16X8);
            if (flags & BWD0)
                ff_cavs_mv(h, MV_BWD_X0, MV_BWD_C2, MV_PRED_TOP,  BLK_16X8, 0);
            if (flags & BWD1)
                ff_cavs_mv(h, MV_BWD_X2, MV_BWD_A1, MV_PRED_LEFT, BLK_16X8, 0);
        } else {          /* 8x16 macroblock types */
            if (flags & FWD0)
                ff_cavs_mv(h, MV_FWD_X0, MV_FWD_B3, MV_PRED_LEFT, BLK_8X16, 1);
            if (flags & SYM0)
                mv_pred_sym(h, &h->mv[MV_FWD_X0], BLK_8X16);
            if (flags & FWD1)
                ff_cavs_mv(h, MV_FWD_X1, MV_FWD_C2, MV_PRED_TOPRIGHT, BLK_8X16, 1);
            if (flags & SYM1)
                mv_pred_sym(h, &h->mv[MV_FWD_X1], BLK_8X16);
            if (flags & BWD0)
                ff_cavs_mv(h, MV_BWD_X0, MV_BWD_B3, MV_PRED_LEFT, BLK_8X16, 0);
            if (flags & BWD1)
                ff_cavs_mv(h, MV_BWD_X1, MV_BWD_C2, MV_PRED_TOPRIGHT, BLK_8X16, 0);
        }
    }
    ff_cavs_inter(h, mb_type);
    set_intra_mode_default(h);
    if (mb_type != B_SKIP)
        decode_residual_inter(h);
    ff_cavs_filter(h, mb_type);

    return 0;
}