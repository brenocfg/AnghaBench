#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* setup_spatial_compensation ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ;} ;
struct TYPE_8__ {int edges; int orient; int chroma_orient; int quant_dc_chroma; int quant; int flat_dc; int predicted_dc; int raw_orient; TYPE_2__* frame; int /*<<< orphan*/  scratchpad; int /*<<< orphan*/ * dest; TYPE_1__ dsp; } ;
struct TYPE_7__ {int /*<<< orphan*/ * linesize; } ;
typedef  TYPE_3__ IntraX8Context ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 int x8_get_orient_vlc (TYPE_3__* const) ; 

__attribute__((used)) static int x8_setup_spatial_predictor(IntraX8Context *const w, const int chroma)
{
    int range;
    int sum;
    int quant;

    w->dsp.setup_spatial_compensation(w->dest[chroma], w->scratchpad,
                                      w->frame->linesize[chroma > 0],
                                      &range, &sum, w->edges);
    if (chroma) {
        w->orient = w->chroma_orient;
        quant     = w->quant_dc_chroma;
    } else {
        quant = w->quant;
    }

    w->flat_dc = 0;
    if (range < quant || range < 3) {
        w->orient = 0;

        // yep you read right, a +-1 idct error may break decoding!
        if (range < 3) {
            w->flat_dc      = 1;
            sum            += 9;
            // ((1 << 17) + 9) / (8 + 8 + 1 + 2) = 6899
            w->predicted_dc = sum * 6899 >> 17;
        }
    }
    if (chroma)
        return 0;

    av_assert2(w->orient < 3);
    if (range < 2 * w->quant) {
        if ((w->edges & 3) == 0) {
            if (w->orient == 1)
                w->orient = 11;
            if (w->orient == 2)
                w->orient = 10;
        } else {
            w->orient = 0;
        }
        w->raw_orient = 0;
    } else {
        static const uint8_t prediction_table[3][12] = {
            { 0, 8, 4, 10, 11, 2, 6, 9, 1, 3, 5, 7 },
            { 4, 0, 8, 11, 10, 3, 5, 2, 6, 9, 1, 7 },
            { 8, 0, 4, 10, 11, 1, 7, 2, 6, 9, 3, 5 },
        };
        w->raw_orient = x8_get_orient_vlc(w);
        if (w->raw_orient < 0)
            return -1;
        av_assert2(w->raw_orient < 12);
        av_assert2(w->orient < 3);
        w->orient=prediction_table[w->orient][w->raw_orient];
    }
    return 0;
}