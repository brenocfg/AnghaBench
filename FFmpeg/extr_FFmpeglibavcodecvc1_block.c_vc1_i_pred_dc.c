#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_3__ {int y_dc_scale; int c_dc_scale; int* block_wrap; int** dc_val; int* block_index; scalar_t__ mb_x; scalar_t__ first_slice_line; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ abs (int) ; 

__attribute__((used)) static inline int vc1_i_pred_dc(MpegEncContext *s, int overlap, int pq, int n,
                                int16_t **dc_val_ptr, int *dir_ptr)
{
    int a, b, c, wrap, pred, scale;
    int16_t *dc_val;
    static const uint16_t dcpred[32] = {
        -1, 1024,  512,  341,  256,  205,  171,  146,  128,
             114,  102,   93,   85,   79,   73,   68,   64,
              60,   57,   54,   51,   49,   47,   45,   43,
              41,   39,   38,   37,   35,   34,   33
    };

    /* find prediction - wmv3_dc_scale always used here in fact */
    if (n < 4) scale = s->y_dc_scale;
    else       scale = s->c_dc_scale;

    wrap   = s->block_wrap[n];
    dc_val = s->dc_val[0] + s->block_index[n];

    /* B A
     * C X
     */
    c = dc_val[ - 1];
    b = dc_val[ - 1 - wrap];
    a = dc_val[ - wrap];

    if (pq < 9 || !overlap) {
        /* Set outer values */
        if (s->first_slice_line && (n != 2 && n != 3))
            b = a = dcpred[scale];
        if (s->mb_x == 0 && (n != 1 && n != 3))
            b = c = dcpred[scale];
    } else {
        /* Set outer values */
        if (s->first_slice_line && (n != 2 && n != 3))
            b = a = 0;
        if (s->mb_x == 0 && (n != 1 && n != 3))
            b = c = 0;
    }

    if (abs(a - b) <= abs(b - c)) {
        pred     = c;
        *dir_ptr = 1; // left
    } else {
        pred     = a;
        *dir_ptr = 0; // top
    }

    /* update predictor */
    *dc_val_ptr = &dc_val[0];
    return pred;
}