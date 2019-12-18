#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ err; } ;
struct TYPE_11__ {int /*<<< orphan*/  hash; scalar_t__ stack_pos; TYPE_1__ els_ctx; scalar_t__ next_run_pos; } ;
typedef  TYPE_2__ ePICContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int epic_add_pixel_to_cache (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  epic_cache_entries_for_pixel (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  epic_decode_from_cache (TYPE_2__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ epic_decode_pixel_pred (TYPE_2__*,int,int,scalar_t__*,scalar_t__*) ; 
 int epic_decode_run_length (TYPE_2__*,int,int,int,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int*) ; 
 int epic_handle_edges (TYPE_2__*,int,int,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  epic_predict_from_NW_NE (TYPE_2__*,int,int,int,int,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ is_pixel_on_stack (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int epic_decode_tile(ePICContext *dc, uint8_t *out, int tile_height,
                            int tile_width, int stride)
{
    int x, y;
    uint32_t pix;
    uint32_t *curr_row = NULL, *above_row = NULL, *above2_row;

    for (y = 0; y < tile_height; y++, out += stride) {
        above2_row = above_row;
        above_row  = curr_row;
        curr_row   = (uint32_t *) out;

        for (x = 0, dc->next_run_pos = 0; x < tile_width;) {
            if (dc->els_ctx.err)
                return AVERROR_INVALIDDATA; // bail out in the case of ELS overflow

            pix = curr_row[x - 1]; // get W pixel

            if (y >= 1 && x >= 2 &&
                pix != curr_row[x - 2]  && pix != above_row[x - 1] &&
                pix != above_row[x - 2] && pix != above_row[x] &&
                !epic_cache_entries_for_pixel(&dc->hash, pix)) {
                curr_row[x] = epic_decode_pixel_pred(dc, x, y, curr_row, above_row);
                x++;
            } else {
                int got_pixel, run;
                dc->stack_pos = 0; // empty stack

                if (y < 2 || x < 2 || x == tile_width - 1) {
                    run       = 1;
                    got_pixel = epic_handle_edges(dc, x, y, curr_row, above_row, &pix);
                } else {
                    got_pixel = epic_decode_run_length(dc, x, y, tile_width,
                                                       curr_row, above_row,
                                                       above2_row, &pix, &run);
                    if (got_pixel < 0)
                        return got_pixel;
                }

                if (!got_pixel && !epic_predict_from_NW_NE(dc, x, y, run,
                                                           tile_width, curr_row,
                                                           above_row, &pix)) {
                    uint32_t ref_pix = curr_row[x - 1];
                    if (!x || !epic_decode_from_cache(dc, ref_pix, &pix)) {
                        pix = epic_decode_pixel_pred(dc, x, y, curr_row, above_row);
                        if (is_pixel_on_stack(dc, pix))
                            return AVERROR_INVALIDDATA;

                        if (x) {
                            int ret = epic_add_pixel_to_cache(&dc->hash,
                                                              ref_pix,
                                                              pix);
                            if (ret)
                                return ret;
                        }
                    }
                }
                for (; run > 0; x++, run--)
                    curr_row[x] = pix;
            }
        }
    }

    return 0;
}