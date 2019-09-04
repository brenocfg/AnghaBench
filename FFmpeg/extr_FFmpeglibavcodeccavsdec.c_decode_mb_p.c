#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  enum cavs_mb { ____Placeholder_cavs_mb } cavs_mb ;
struct TYPE_10__ {int* col_type_base; size_t mbidx; int /*<<< orphan*/  ref_flag; int /*<<< orphan*/  gb; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_16X16 ; 
 int /*<<< orphan*/  BLK_16X8 ; 
 int /*<<< orphan*/  BLK_8X16 ; 
 int /*<<< orphan*/  BLK_8X8 ; 
 int /*<<< orphan*/  MV_FWD_A1 ; 
 int /*<<< orphan*/  MV_FWD_B3 ; 
 int /*<<< orphan*/  MV_FWD_C2 ; 
 int /*<<< orphan*/  MV_FWD_X0 ; 
 int /*<<< orphan*/  MV_FWD_X1 ; 
 int /*<<< orphan*/  MV_FWD_X2 ; 
 int /*<<< orphan*/  MV_FWD_X3 ; 
 int /*<<< orphan*/  MV_PRED_LEFT ; 
 int /*<<< orphan*/  MV_PRED_MEDIAN ; 
 int /*<<< orphan*/  MV_PRED_PSKIP ; 
 int /*<<< orphan*/  MV_PRED_TOP ; 
 int /*<<< orphan*/  MV_PRED_TOPRIGHT ; 
#define  P_16X16 132 
#define  P_16X8 131 
#define  P_8X16 130 
#define  P_8X8 129 
#define  P_SKIP 128 
 int /*<<< orphan*/  decode_residual_inter (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_cavs_filter (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_cavs_init_mb (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_cavs_inter (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_cavs_mv (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_intra_mode_default (TYPE_1__*) ; 
 int /*<<< orphan*/  store_mvs (TYPE_1__*) ; 

__attribute__((used)) static void decode_mb_p(AVSContext *h, enum cavs_mb mb_type)
{
    GetBitContext *gb = &h->gb;
    int ref[4];

    ff_cavs_init_mb(h);
    switch (mb_type) {
    case P_SKIP:
        ff_cavs_mv(h, MV_FWD_X0, MV_FWD_C2, MV_PRED_PSKIP,  BLK_16X16, 0);
        break;
    case P_16X16:
        ref[0] = h->ref_flag ? 0 : get_bits1(gb);
        ff_cavs_mv(h, MV_FWD_X0, MV_FWD_C2, MV_PRED_MEDIAN, BLK_16X16, ref[0]);
        break;
    case P_16X8:
        ref[0] = h->ref_flag ? 0 : get_bits1(gb);
        ref[2] = h->ref_flag ? 0 : get_bits1(gb);
        ff_cavs_mv(h, MV_FWD_X0, MV_FWD_C2, MV_PRED_TOP,    BLK_16X8, ref[0]);
        ff_cavs_mv(h, MV_FWD_X2, MV_FWD_A1, MV_PRED_LEFT,   BLK_16X8, ref[2]);
        break;
    case P_8X16:
        ref[0] = h->ref_flag ? 0 : get_bits1(gb);
        ref[1] = h->ref_flag ? 0 : get_bits1(gb);
        ff_cavs_mv(h, MV_FWD_X0, MV_FWD_B3, MV_PRED_LEFT,     BLK_8X16, ref[0]);
        ff_cavs_mv(h, MV_FWD_X1, MV_FWD_C2, MV_PRED_TOPRIGHT, BLK_8X16, ref[1]);
        break;
    case P_8X8:
        ref[0] = h->ref_flag ? 0 : get_bits1(gb);
        ref[1] = h->ref_flag ? 0 : get_bits1(gb);
        ref[2] = h->ref_flag ? 0 : get_bits1(gb);
        ref[3] = h->ref_flag ? 0 : get_bits1(gb);
        ff_cavs_mv(h, MV_FWD_X0, MV_FWD_B3, MV_PRED_MEDIAN,   BLK_8X8, ref[0]);
        ff_cavs_mv(h, MV_FWD_X1, MV_FWD_C2, MV_PRED_MEDIAN,   BLK_8X8, ref[1]);
        ff_cavs_mv(h, MV_FWD_X2, MV_FWD_X1, MV_PRED_MEDIAN,   BLK_8X8, ref[2]);
        ff_cavs_mv(h, MV_FWD_X3, MV_FWD_X0, MV_PRED_MEDIAN,   BLK_8X8, ref[3]);
    }
    ff_cavs_inter(h, mb_type);
    set_intra_mode_default(h);
    store_mvs(h);
    if (mb_type != P_SKIP)
        decode_residual_inter(h);
    ff_cavs_filter(h, mb_type);
    h->col_type_base[h->mbidx] = mb_type;
}