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
struct TYPE_4__ {int next_run_pos; int /*<<< orphan*/ * W_ctx_rung; int /*<<< orphan*/  els_ctx; int /*<<< orphan*/ * runlen_zeroes; int /*<<< orphan*/  runlen_one; int /*<<< orphan*/ * prev_row_rung; int /*<<< orphan*/  stack_pos; scalar_t__* stack; int /*<<< orphan*/ * N_ctx_rung; } ;
typedef  TYPE_1__ ePICContext ;

/* Variables and functions */
 size_t EPIC_PIX_STACK_MAX ; 
 int /*<<< orphan*/  LOAD_NEIGHBOURS (int) ; 
 int /*<<< orphan*/  UPDATE_NEIGHBOURS (int) ; 
 int av_ceil_log2 (int) ; 
 int ff_els_decode_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_pixel_on_stack (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int epic_decode_run_length(ePICContext *dc, int x, int y, int tile_width,
                                  const uint32_t *curr_row,
                                  const uint32_t *above_row,
                                  const uint32_t *above2_row,
                                  uint32_t *pPix, int *pRun)
{
    int idx, got_pixel = 0, WWneW, old_WWneW = 0;
    uint32_t W, WW, N, NN, NW, NE, NWW, NNW, NNE;

    *pRun = 0;

    LOAD_NEIGHBOURS(x);

    if (dc->next_run_pos == x) {
        /* can't reuse W for the new pixel in this case */
        WWneW = 1;
    } else {
        idx = (WW  != W)  << 7 |
              (NW  != W)  << 6 |
              (N   != NE) << 5 |
              (NW  != N)  << 4 |
              (NWW != NW) << 3 |
              (NNE != NE) << 2 |
              (NN  != N)  << 1 |
              (NNW != NW);
        WWneW = ff_els_decode_bit(&dc->els_ctx, &dc->W_ctx_rung[idx]);
        if (WWneW < 0)
            return WWneW;
    }

    if (WWneW)
        dc->stack[dc->stack_pos++ & EPIC_PIX_STACK_MAX] = W;
    else {
        *pPix     = W;
        got_pixel = 1;
    }

    do {
        int NWneW = 1;
        if (got_pixel) // pixel value already known (derived from either W or N)
            NWneW = *pPix != N;
        else { // pixel value is unknown and will be decoded later
            NWneW = *pRun ? NWneW : NW != W;

            /* TODO: RFC this mess! */
            switch (((NW != N) << 2) | (NWneW << 1) | WWneW) {
            case 0:
                break; // do nothing here
            case 3:
            case 5:
            case 6:
            case 7:
                if (!is_pixel_on_stack(dc, N)) {
                    idx = WWneW       << 8 |
                          (*pRun ? old_WWneW : WW != W) << 7 |
                          NWneW       << 6 |
                          (N   != NE) << 5 |
                          (NW  != N)  << 4 |
                          (NWW != NW) << 3 |
                          (NNE != NE) << 2 |
                          (NN  != N)  << 1 |
                          (NNW != NW);
                    if (!ff_els_decode_bit(&dc->els_ctx, &dc->N_ctx_rung[idx])) {
                        NWneW = 0;
                        *pPix = N;
                        got_pixel = 1;
                        break;
                    }
                }
                /* fall through */
            default:
                NWneW = 1;
                old_WWneW = WWneW;
                if (!is_pixel_on_stack(dc, N))
                    dc->stack[dc->stack_pos++ & EPIC_PIX_STACK_MAX] = N;
            }
        }

        (*pRun)++;
        if (x + *pRun >= tile_width - 1)
            break;

        UPDATE_NEIGHBOURS(x + *pRun);

        if (!NWneW && NW == N && N == NE) {
            int pos, run, rle;
            int start_pos = x + *pRun;

            /* scan for a run of pix in the line above */
            uint32_t pix = above_row[start_pos + 1];
            for (pos = start_pos + 2; pos < tile_width; pos++)
                if (!(above_row[pos] == pix))
                    break;
            run = pos - start_pos - 1;
            idx = av_ceil_log2(run);
            if (ff_els_decode_bit(&dc->els_ctx, &dc->prev_row_rung[idx]))
                *pRun += run;
            else {
                int flag;
                /* run-length is coded as plain binary number of idx - 1 bits */
                for (pos = idx - 1, rle = 0, flag = 0; pos >= 0; pos--) {
                    if ((1 << pos) + rle < run &&
                        ff_els_decode_bit(&dc->els_ctx,
                                          flag ? &dc->runlen_one
                                               : &dc->runlen_zeroes[pos])) {
                        flag = 1;
                        rle |= 1 << pos;
                    }
                }
                *pRun += rle;
                break; // return immediately
            }
            if (x + *pRun >= tile_width - 1)
                break;

            LOAD_NEIGHBOURS(x + *pRun);
            WWneW = 0;
            NWneW = 0;
        }

        idx = WWneW       << 7 |
              NWneW       << 6 |
              (N   != NE) << 5 |
              (NW  != N)  << 4 |
              (NWW != NW) << 3 |
              (NNE != NE) << 2 |
              (NN  != N)  << 1 |
              (NNW != NW);
        WWneW = ff_els_decode_bit(&dc->els_ctx, &dc->W_ctx_rung[idx]);
    } while (!WWneW);

    dc->next_run_pos = x + *pRun;
    return got_pixel;
}