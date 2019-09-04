#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* sps; } ;
struct TYPE_15__ {int* tab_ipm; TYPE_3__* ref; TYPE_2__ ps; TYPE_6__* HEVClc; } ;
struct TYPE_12__ {size_t mpm_idx; int rem_intra_luma_pred_mode; } ;
struct TYPE_14__ {TYPE_4__ pu; scalar_t__ ctb_left_flag; scalar_t__ ctb_up_flag; } ;
struct TYPE_13__ {int /*<<< orphan*/  pred_flag; } ;
struct TYPE_11__ {TYPE_5__* tab_mvf; } ;
struct TYPE_9__ {int log2_min_pu_size; int min_pu_width; int log2_ctb_size; } ;
typedef  TYPE_5__ MvField ;
typedef  TYPE_6__ HEVCLocalContext ;
typedef  TYPE_7__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFSWAP (int /*<<< orphan*/ ,int,int) ; 
 int INTRA_ANGULAR_26 ; 
 int INTRA_DC ; 
 int INTRA_PLANAR ; 
 int /*<<< orphan*/  PF_INTRA ; 
 int av_mod_uintp2 (int,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  uint8_t ; 

__attribute__((used)) static int luma_intra_pred_mode(HEVCContext *s, int x0, int y0, int pu_size,
                                int prev_intra_luma_pred_flag)
{
    HEVCLocalContext *lc = s->HEVClc;
    int x_pu             = x0 >> s->ps.sps->log2_min_pu_size;
    int y_pu             = y0 >> s->ps.sps->log2_min_pu_size;
    int min_pu_width     = s->ps.sps->min_pu_width;
    int size_in_pus      = pu_size >> s->ps.sps->log2_min_pu_size;
    int x0b              = av_mod_uintp2(x0, s->ps.sps->log2_ctb_size);
    int y0b              = av_mod_uintp2(y0, s->ps.sps->log2_ctb_size);

    int cand_up   = (lc->ctb_up_flag || y0b) ?
                    s->tab_ipm[(y_pu - 1) * min_pu_width + x_pu] : INTRA_DC;
    int cand_left = (lc->ctb_left_flag || x0b) ?
                    s->tab_ipm[y_pu * min_pu_width + x_pu - 1]   : INTRA_DC;

    int y_ctb = (y0 >> (s->ps.sps->log2_ctb_size)) << (s->ps.sps->log2_ctb_size);

    MvField *tab_mvf = s->ref->tab_mvf;
    int intra_pred_mode;
    int candidate[3];
    int i, j;

    // intra_pred_mode prediction does not cross vertical CTB boundaries
    if ((y0 - 1) < y_ctb)
        cand_up = INTRA_DC;

    if (cand_left == cand_up) {
        if (cand_left < 2) {
            candidate[0] = INTRA_PLANAR;
            candidate[1] = INTRA_DC;
            candidate[2] = INTRA_ANGULAR_26;
        } else {
            candidate[0] = cand_left;
            candidate[1] = 2 + ((cand_left - 2 - 1 + 32) & 31);
            candidate[2] = 2 + ((cand_left - 2 + 1) & 31);
        }
    } else {
        candidate[0] = cand_left;
        candidate[1] = cand_up;
        if (candidate[0] != INTRA_PLANAR && candidate[1] != INTRA_PLANAR) {
            candidate[2] = INTRA_PLANAR;
        } else if (candidate[0] != INTRA_DC && candidate[1] != INTRA_DC) {
            candidate[2] = INTRA_DC;
        } else {
            candidate[2] = INTRA_ANGULAR_26;
        }
    }

    if (prev_intra_luma_pred_flag) {
        intra_pred_mode = candidate[lc->pu.mpm_idx];
    } else {
        if (candidate[0] > candidate[1])
            FFSWAP(uint8_t, candidate[0], candidate[1]);
        if (candidate[0] > candidate[2])
            FFSWAP(uint8_t, candidate[0], candidate[2]);
        if (candidate[1] > candidate[2])
            FFSWAP(uint8_t, candidate[1], candidate[2]);

        intra_pred_mode = lc->pu.rem_intra_luma_pred_mode;
        for (i = 0; i < 3; i++)
            if (intra_pred_mode >= candidate[i])
                intra_pred_mode++;
    }

    /* write the intra prediction units into the mv array */
    if (!size_in_pus)
        size_in_pus = 1;
    for (i = 0; i < size_in_pus; i++) {
        memset(&s->tab_ipm[(y_pu + i) * min_pu_width + x_pu],
               intra_pred_mode, size_in_pus);

        for (j = 0; j < size_in_pus; j++) {
            tab_mvf[(y_pu + j) * min_pu_width + x_pu + i].pred_flag = PF_INTRA;
        }
    }

    return intra_pred_mode;
}