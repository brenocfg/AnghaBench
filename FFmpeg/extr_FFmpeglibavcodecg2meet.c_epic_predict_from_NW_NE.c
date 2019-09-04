#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int const uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/ * ne_pred_rung; int /*<<< orphan*/ * nw_pred_rung; } ;
typedef  TYPE_1__ ePICContext ;

/* Variables and functions */
 scalar_t__ epic_predict_pixel2 (TYPE_1__*,int /*<<< orphan*/ *,int const*,int const) ; 
 int /*<<< orphan*/  is_pixel_on_stack (TYPE_1__*,int const) ; 

__attribute__((used)) static int epic_predict_from_NW_NE(ePICContext *dc, int x, int y, int run,
                                   int tile_width, const uint32_t *curr_row,
                                   const uint32_t *above_row, uint32_t *pPix)
{
    int pos;

    /* try to reuse the NW pixel first */
    if (x && y) {
        uint32_t NW = above_row[x - 1];
        if (NW != curr_row[x - 1] && NW != above_row[x] && !is_pixel_on_stack(dc, NW)) {
            if (epic_predict_pixel2(dc, &dc->nw_pred_rung[NW & 0xFF], pPix, NW))
                return 1;
        }
    }

    /* try to reuse the NE[x + run, y] pixel */
    pos = x + run - 1;
    if (pos < tile_width - 1 && y) {
        uint32_t NE = above_row[pos + 1];
        if (NE != above_row[pos] && !is_pixel_on_stack(dc, NE)) {
            if (epic_predict_pixel2(dc, &dc->ne_pred_rung[NE & 0xFF], pPix, NE))
                return 1;
        }
    }

    return 0;
}