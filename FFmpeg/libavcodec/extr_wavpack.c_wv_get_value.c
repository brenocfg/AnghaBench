#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int* median; int error_limit; int /*<<< orphan*/  slow_level; } ;
typedef  TYPE_1__ WvChannel ;
struct TYPE_6__ {int zero; int one; int zeroes; int /*<<< orphan*/  avctx; scalar_t__ hybrid_bitrate; scalar_t__ hybrid; TYPE_1__* ch; } ;
typedef  TYPE_2__ WavpackFrameContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DEC_MED (int) ; 
 int GET_MED (int) ; 
 int /*<<< orphan*/  INC_MED (int) ; 
 scalar_t__ LEVEL_DECAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int get_tail (int /*<<< orphan*/ *,int) ; 
 int get_unary_0_33 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ update_error_limit (TYPE_2__*) ; 
 scalar_t__ wp_log2 (int) ; 

__attribute__((used)) static int wv_get_value(WavpackFrameContext *ctx, GetBitContext *gb,
                        int channel, int *last)
{
    int t, t2;
    int sign, base, add, ret;
    WvChannel *c = &ctx->ch[channel];

    *last = 0;

    if ((ctx->ch[0].median[0] < 2U) && (ctx->ch[1].median[0] < 2U) &&
        !ctx->zero && !ctx->one) {
        if (ctx->zeroes) {
            ctx->zeroes--;
            if (ctx->zeroes) {
                c->slow_level -= LEVEL_DECAY(c->slow_level);
                return 0;
            }
        } else {
            t = get_unary_0_33(gb);
            if (t >= 2) {
                if (t >= 32 || get_bits_left(gb) < t - 1)
                    goto error;
                t = get_bits_long(gb, t - 1) | (1 << (t - 1));
            } else {
                if (get_bits_left(gb) < 0)
                    goto error;
            }
            ctx->zeroes = t;
            if (ctx->zeroes) {
                memset(ctx->ch[0].median, 0, sizeof(ctx->ch[0].median));
                memset(ctx->ch[1].median, 0, sizeof(ctx->ch[1].median));
                c->slow_level -= LEVEL_DECAY(c->slow_level);
                return 0;
            }
        }
    }

    if (ctx->zero) {
        t         = 0;
        ctx->zero = 0;
    } else {
        t = get_unary_0_33(gb);
        if (get_bits_left(gb) < 0)
            goto error;
        if (t == 16) {
            t2 = get_unary_0_33(gb);
            if (t2 < 2) {
                if (get_bits_left(gb) < 0)
                    goto error;
                t += t2;
            } else {
                if (t2 >= 32 || get_bits_left(gb) < t2 - 1)
                    goto error;
                t += get_bits_long(gb, t2 - 1) | (1 << (t2 - 1));
            }
        }

        if (ctx->one) {
            ctx->one = t & 1;
            t        = (t >> 1) + 1;
        } else {
            ctx->one = t & 1;
            t      >>= 1;
        }
        ctx->zero = !ctx->one;
    }

    if (ctx->hybrid && !channel) {
        if (update_error_limit(ctx) < 0)
            goto error;
    }

    if (!t) {
        base = 0;
        add  = GET_MED(0) - 1;
        DEC_MED(0);
    } else if (t == 1) {
        base = GET_MED(0);
        add  = GET_MED(1) - 1;
        INC_MED(0);
        DEC_MED(1);
    } else if (t == 2) {
        base = GET_MED(0) + GET_MED(1);
        add  = GET_MED(2) - 1;
        INC_MED(0);
        INC_MED(1);
        DEC_MED(2);
    } else {
        base = GET_MED(0) + GET_MED(1) + GET_MED(2) * (t - 2U);
        add  = GET_MED(2) - 1;
        INC_MED(0);
        INC_MED(1);
        INC_MED(2);
    }
    if (!c->error_limit) {
        if (add >= 0x2000000U) {
            av_log(ctx->avctx, AV_LOG_ERROR, "k %d is too large\n", add);
            goto error;
        }
        ret = base + get_tail(gb, add);
        if (get_bits_left(gb) <= 0)
            goto error;
    } else {
        int mid = (base * 2U + add + 1) >> 1;
        while (add > c->error_limit) {
            if (get_bits_left(gb) <= 0)
                goto error;
            if (get_bits1(gb)) {
                add -= (mid - (unsigned)base);
                base = mid;
            } else
                add = mid - (unsigned)base - 1;
            mid = (base * 2U + add + 1) >> 1;
        }
        ret = mid;
    }
    sign = get_bits1(gb);
    if (ctx->hybrid_bitrate)
        c->slow_level += wp_log2(ret) - LEVEL_DECAY(c->slow_level);
    return sign ? ~ret : ret;

error:
    ret = get_bits_left(gb);
    if (ret <= 0) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Too few bits (%d) left\n", ret);
    }
    *last = 1;
    return 0;
}