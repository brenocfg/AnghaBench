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
typedef  int uint8_t ;
typedef  int int8_t ;
struct TYPE_3__ {int /*<<< orphan*/  avctx; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int EXP_D45 ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int** ungroup_3_in_7_bits_tab ; 

__attribute__((used)) static int decode_exponents(AC3DecodeContext *s,
                            GetBitContext *gbc, int exp_strategy, int ngrps,
                            uint8_t absexp, int8_t *dexps)
{
    int i, j, grp, group_size;
    int dexp[256];
    int expacc, prevexp;

    /* unpack groups */
    group_size = exp_strategy + (exp_strategy == EXP_D45);
    for (grp = 0, i = 0; grp < ngrps; grp++) {
        expacc = get_bits(gbc, 7);
        if (expacc >= 125) {
            av_log(s->avctx, AV_LOG_ERROR, "expacc %d is out-of-range\n", expacc);
            return AVERROR_INVALIDDATA;
        }
        dexp[i++] = ungroup_3_in_7_bits_tab[expacc][0];
        dexp[i++] = ungroup_3_in_7_bits_tab[expacc][1];
        dexp[i++] = ungroup_3_in_7_bits_tab[expacc][2];
    }

    /* convert to absolute exps and expand groups */
    prevexp = absexp;
    for (i = 0, j = 0; i < ngrps * 3; i++) {
        prevexp += dexp[i] - 2;
        if (prevexp > 24U) {
            av_log(s->avctx, AV_LOG_ERROR, "exponent %d is out-of-range\n", prevexp);
            return AVERROR_INVALIDDATA;
        }
        switch (group_size) {
        case 4: dexps[j++] = prevexp;
                dexps[j++] = prevexp;
        case 2: dexps[j++] = prevexp;
        case 1: dexps[j++] = prevexp;
        }
    }
    return 0;
}