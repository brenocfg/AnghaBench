#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__* stack; int /*<<< orphan*/  N_flag_rung; int /*<<< orphan*/  stack_pos; int /*<<< orphan*/  W_flag_rung; int /*<<< orphan*/  unsigned_rung; int /*<<< orphan*/  els_ctx; } ;
typedef  TYPE_1__ ePICContext ;

/* Variables and functions */
 scalar_t__ B_shift ; 
 scalar_t__ G_shift ; 
 scalar_t__ R_shift ; 
 scalar_t__ epic_predict_pixel (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 scalar_t__ ff_els_decode_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int epic_handle_edges(ePICContext *dc, int x, int y,
                             const uint32_t *curr_row,
                             const uint32_t *above_row, uint32_t *pPix)
{
    uint32_t pix;

    if (!x && !y) { /* special case: top-left pixel */
        /* the top-left pixel is coded independently with 3 unsigned numbers */
        *pPix = (ff_els_decode_unsigned(&dc->els_ctx, &dc->unsigned_rung) << R_shift) |
                (ff_els_decode_unsigned(&dc->els_ctx, &dc->unsigned_rung) << G_shift) |
                (ff_els_decode_unsigned(&dc->els_ctx, &dc->unsigned_rung) << B_shift);
        return 1;
    }

    if (x) { /* predict from W first */
        pix = curr_row[x - 1];
        if (epic_predict_pixel(dc, &dc->W_flag_rung, pPix, pix))
            return 1;
    }

    if (y) { /* then try to predict from N */
        pix = above_row[x];
        if (!dc->stack_pos || dc->stack[0] != pix) {
            if (epic_predict_pixel(dc, &dc->N_flag_rung, pPix, pix))
                return 1;
        }
    }

    return 0;
}