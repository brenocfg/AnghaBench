#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_10__ {int blocksize; } ;
struct TYPE_8__ {int lpc_coeff_precision; } ;
struct TYPE_12__ {TYPE_3__ frame; TYPE_1__ options; } ;
struct TYPE_9__ {int porder; int* params; scalar_t__ coding_mode; } ;
struct TYPE_11__ {scalar_t__ type; int obits; int /*<<< orphan*/ * residual; TYPE_2__ rc; scalar_t__ wasted; } ;
typedef  TYPE_4__ FlacSubframe ;
typedef  TYPE_5__ FlacEncodeContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 scalar_t__ FLAC_SUBFRAME_CONSTANT ; 
 scalar_t__ FLAC_SUBFRAME_LPC ; 
 scalar_t__ FLAC_SUBFRAME_VERBATIM ; 
 scalar_t__ rice_count_exact (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static uint64_t subframe_count_exact(FlacEncodeContext *s, FlacSubframe *sub,
                                     int pred_order)
{
    int p, porder, psize;
    int i, part_end;
    uint64_t count = 0;

    /* subframe header */
    count += 8;

    if (sub->wasted)
        count += sub->wasted;

    /* subframe */
    if (sub->type == FLAC_SUBFRAME_CONSTANT) {
        count += sub->obits;
    } else if (sub->type == FLAC_SUBFRAME_VERBATIM) {
        count += s->frame.blocksize * sub->obits;
    } else {
        /* warm-up samples */
        count += pred_order * sub->obits;

        /* LPC coefficients */
        if (sub->type == FLAC_SUBFRAME_LPC)
            count += 4 + 5 + pred_order * s->options.lpc_coeff_precision;

        /* rice-encoded block */
        count += 2;

        /* partition order */
        porder = sub->rc.porder;
        psize  = s->frame.blocksize >> porder;
        count += 4;

        /* residual */
        i        = pred_order;
        part_end = psize;
        for (p = 0; p < 1 << porder; p++) {
            int k = sub->rc.params[p];
            count += sub->rc.coding_mode;
            count += rice_count_exact(&sub->residual[i], part_end - i, k);
            i = part_end;
            part_end = FFMIN(s->frame.blocksize, part_end + psize);
        }
    }

    return count;
}