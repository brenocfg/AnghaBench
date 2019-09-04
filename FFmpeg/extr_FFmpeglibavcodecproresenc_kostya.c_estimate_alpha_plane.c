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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int int16_t ;
struct TYPE_3__ {int alpha_bits; } ;
typedef  TYPE_1__ ProresContext ;

/* Variables and functions */
 int est_alpha_diff (int,int,int const) ; 

__attribute__((used)) static int estimate_alpha_plane(ProresContext *ctx,
                                const uint16_t *src, ptrdiff_t linesize,
                                int mbs_per_slice, int16_t *blocks)
{
    const int abits = ctx->alpha_bits;
    const int mask  = (1 << abits) - 1;
    const int num_coeffs = mbs_per_slice * 256;
    int prev = mask, cur;
    int idx = 0;
    int run = 0;
    int bits;

    cur = blocks[idx++];
    bits = est_alpha_diff(cur, prev, abits);
    prev = cur;
    do {
        cur = blocks[idx++];
        if (cur != prev) {
            if (!run)
                bits++;
            else if (run < 0x10)
                bits += 4;
            else
                bits += 15;
            bits += est_alpha_diff(cur, prev, abits);
            prev = cur;
            run  = 0;
        } else {
            run++;
        }
    } while (idx < num_coeffs);

    if (run) {
        if (run < 0x10)
            bits += 4;
        else
            bits += 15;
    }

    return bits;
}