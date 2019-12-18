#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* priv_data; } ;
struct TYPE_10__ {int mbs_per_slice; int mb_width; int slices_width; int /*<<< orphan*/ * slice_q; TYPE_2__* tdata; } ;
struct TYPE_9__ {TYPE_1__* nodes; } ;
struct TYPE_8__ {int prev_node; int /*<<< orphan*/  quant; } ;
typedef  TYPE_2__ ProresThreadData ;
typedef  TYPE_3__ ProresContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int TRELLIS_WIDTH ; 
 int find_slice_quant (TYPE_4__*,int,int,int,int,TYPE_2__*) ; 

__attribute__((used)) static int find_quant_thread(AVCodecContext *avctx, void *arg,
                             int jobnr, int threadnr)
{
    ProresContext *ctx = avctx->priv_data;
    ProresThreadData *td = ctx->tdata + threadnr;
    int mbs_per_slice = ctx->mbs_per_slice;
    int x, y = jobnr, mb, q = 0;

    for (x = mb = 0; x < ctx->mb_width; x += mbs_per_slice, mb++) {
        while (ctx->mb_width - x < mbs_per_slice)
            mbs_per_slice >>= 1;
        q = find_slice_quant(avctx,
                             (mb + 1) * TRELLIS_WIDTH, x, y,
                             mbs_per_slice, td);
    }

    for (x = ctx->slices_width - 1; x >= 0; x--) {
        ctx->slice_q[x + y * ctx->slices_width] = td->nodes[q].quant;
        q = td->nodes[q].prev_node;
    }

    return 0;
}