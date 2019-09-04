#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int dquant; int quant; int qsum; int loopfilter; int mb_x; int mb_y; int divide_quant_dc_luma; int quant_dc_chroma; int divide_quant_dc_chroma; int mb_height; int mb_width; int* dest; int /*<<< orphan*/  frame; int /*<<< orphan*/  avctx; int /*<<< orphan*/ * gb; int /*<<< orphan*/  use_quant_matrix; } ;
struct TYPE_11__ {int* qscale_table; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ Picture ;
typedef  TYPE_2__ IntraX8Context ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  PICT_FRAME ; 
 int /*<<< orphan*/  ff_draw_horiz_band (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ x8_decode_intra_mb (TYPE_2__*,int) ; 
 int /*<<< orphan*/  x8_get_prediction (TYPE_2__*) ; 
 int /*<<< orphan*/  x8_get_prediction_chroma (TYPE_2__*) ; 
 int /*<<< orphan*/  x8_init_block_index (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x8_reset_vlc_tables (TYPE_2__*) ; 
 scalar_t__ x8_setup_spatial_predictor (TYPE_2__*,int) ; 

int ff_intrax8_decode_picture(IntraX8Context *w, Picture *pict,
                              GetBitContext *gb, int *mb_x, int *mb_y,
                              int dquant, int quant_offset,
                              int loopfilter, int lowdelay)
{
    int mb_xy;

    w->gb     = gb;
    w->dquant = dquant;
    w->quant  = dquant >> 1;
    w->qsum   = quant_offset;
    w->frame  = pict->f;
    w->loopfilter = loopfilter;
    w->use_quant_matrix = get_bits1(w->gb);

    w->mb_x = *mb_x;
    w->mb_y = *mb_y;

    w->divide_quant_dc_luma = ((1 << 16) + (w->quant >> 1)) / w->quant;
    if (w->quant < 5) {
        w->quant_dc_chroma        = w->quant;
        w->divide_quant_dc_chroma = w->divide_quant_dc_luma;
    } else {
        w->quant_dc_chroma        = w->quant + ((w->quant + 3) >> 3);
        w->divide_quant_dc_chroma = ((1 << 16) + (w->quant_dc_chroma >> 1)) / w->quant_dc_chroma;
    }
    x8_reset_vlc_tables(w);

    for (w->mb_y = 0; w->mb_y < w->mb_height * 2; w->mb_y++) {
        x8_init_block_index(w, w->frame);
        mb_xy = (w->mb_y >> 1) * (w->mb_width + 1);
        for (w->mb_x = 0; w->mb_x < w->mb_width * 2; w->mb_x++) {
            x8_get_prediction(w);
            if (x8_setup_spatial_predictor(w, 0))
                goto error;
            if (x8_decode_intra_mb(w, 0))
                goto error;

            if (w->mb_x & w->mb_y & 1) {
                x8_get_prediction_chroma(w);

                /* when setting up chroma, no vlc is read,
                 * so no error condition can be reached */
                x8_setup_spatial_predictor(w, 1);
                if (x8_decode_intra_mb(w, 1))
                    goto error;

                x8_setup_spatial_predictor(w, 2);
                if (x8_decode_intra_mb(w, 2))
                    goto error;

                w->dest[1] += 8;
                w->dest[2] += 8;

                pict->qscale_table[mb_xy] = w->quant;
                mb_xy++;
            }
            w->dest[0] += 8;
        }
        if (w->mb_y & 1)
            ff_draw_horiz_band(w->avctx, w->frame, w->frame,
                               (w->mb_y - 1) * 8, 16,
                               PICT_FRAME, 0, lowdelay);
    }

error:
    *mb_x = w->mb_x;
    *mb_y = w->mb_y;

    return 0;
}