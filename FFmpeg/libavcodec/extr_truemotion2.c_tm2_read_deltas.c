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
struct TYPE_3__ {int** deltas; int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ TM2Context ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int TM2_DELTAS ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tm2_read_deltas(TM2Context *ctx, int stream_id)
{
    int d, mb;
    int i, v;

    d  = get_bits(&ctx->gb, 9);
    mb = get_bits(&ctx->gb, 5);

    av_assert2(mb < 32);
    if ((d < 1) || (d > TM2_DELTAS) || (mb < 1)) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Incorrect delta table: %i deltas x %i bits\n", d, mb);
        return AVERROR_INVALIDDATA;
    }

    for (i = 0; i < d; i++) {
        v = get_bits_long(&ctx->gb, mb);
        if (v & (1 << (mb - 1)))
            ctx->deltas[stream_id][i] = v - (1U << mb);
        else
            ctx->deltas[stream_id][i] = v;
    }
    for (; i < TM2_DELTAS; i++)
        ctx->deltas[stream_id][i] = 0;

    return 0;
}