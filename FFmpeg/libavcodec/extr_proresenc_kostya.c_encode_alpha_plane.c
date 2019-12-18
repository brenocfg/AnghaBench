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
struct TYPE_3__ {int alpha_bits; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ ProresContext ;

/* Variables and functions */
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_alpha_diff (int /*<<< orphan*/ *,int,int,int const) ; 
 int /*<<< orphan*/  put_alpha_run (int /*<<< orphan*/ *,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int encode_alpha_plane(ProresContext *ctx, PutBitContext *pb,
                              int mbs_per_slice, uint16_t *blocks,
                              int quant)
{
    const int abits = ctx->alpha_bits;
    const int mask  = (1 << abits) - 1;
    const int num_coeffs = mbs_per_slice * 256;
    int saved_pos = put_bits_count(pb);
    int prev = mask, cur;
    int idx = 0;
    int run = 0;

    cur = blocks[idx++];
    put_alpha_diff(pb, cur, prev, abits);
    prev = cur;
    do {
        cur = blocks[idx++];
        if (cur != prev) {
            put_alpha_run (pb, run);
            put_alpha_diff(pb, cur, prev, abits);
            prev = cur;
            run  = 0;
        } else {
            run++;
        }
    } while (idx < num_coeffs);
    if (run)
        put_alpha_run(pb, run);
    flush_put_bits(pb);
    return (put_bits_count(pb) - saved_pos) >> 3;
}