#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  bits ;
struct TYPE_12__ {int /*<<< orphan*/  (* lpc32_encode ) (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ;int /*<<< orphan*/  (* lpc16_encode ) (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ;} ;
struct TYPE_11__ {int min_prediction_order; int max_prediction_order; int prediction_order_method; int /*<<< orphan*/  lpc_coeff_precision; scalar_t__ multi_dim_quant; int /*<<< orphan*/  lpc_passes; int /*<<< orphan*/  lpc_type; } ;
struct TYPE_14__ {int blocksize; scalar_t__ verbatim_only; TYPE_3__* subframes; } ;
struct TYPE_15__ {int bps_code; TYPE_2__ flac_dsp; TYPE_1__ options; int /*<<< orphan*/  lpc_ctx; TYPE_4__ frame; } ;
struct TYPE_13__ {int type; int type_code; int order; int shift; scalar_t__* coefs; scalar_t__* samples; scalar_t__* residual; } ;
typedef  TYPE_3__ FlacSubframe ;
typedef  TYPE_4__ FlacFrame ;
typedef  TYPE_5__ FlacEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  FF_LPC_TYPE_FIXED ; 
 int /*<<< orphan*/  FF_LPC_TYPE_NONE ; 
 int FLAC_SUBFRAME_CONSTANT ; 
 int FLAC_SUBFRAME_FIXED ; 
 int FLAC_SUBFRAME_LPC ; 
 int FLAC_SUBFRAME_VERBATIM ; 
 scalar_t__ INT64_MAX ; 
 int MAX_FIXED_ORDER ; 
 int MAX_LPC_ORDER ; 
 int /*<<< orphan*/  MAX_LPC_SHIFT ; 
 int /*<<< orphan*/  MIN_LPC_SHIFT ; 
 int ORDER_METHOD_2LEVEL ; 
 int ORDER_METHOD_4LEVEL ; 
 int ORDER_METHOD_8LEVEL ; 
 int ORDER_METHOD_LOG ; 
 int ORDER_METHOD_SEARCH ; 
 scalar_t__ UINT32_MAX ; 
 void* av_clip (scalar_t__,scalar_t__,scalar_t__) ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/  encode_residual_fixed (scalar_t__*,scalar_t__*,int,int) ; 
 int ff_lpc_calc_coefs (int /*<<< orphan*/ *,scalar_t__*,int,int,int,int /*<<< orphan*/ ,scalar_t__**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_subframe_rice_params (TYPE_5__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub10 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub3 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub5 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub6 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub7 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub8 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub9 (scalar_t__*,scalar_t__*,int,int,scalar_t__*,int) ; 
 int subframe_count_exact (TYPE_5__*,TYPE_3__*,int) ; 

__attribute__((used)) static int encode_residual_ch(FlacEncodeContext *s, int ch)
{
    int i, n;
    int min_order, max_order, opt_order, omethod;
    FlacFrame *frame;
    FlacSubframe *sub;
    int32_t coefs[MAX_LPC_ORDER][MAX_LPC_ORDER];
    int shift[MAX_LPC_ORDER];
    int32_t *res, *smp;

    frame = &s->frame;
    sub   = &frame->subframes[ch];
    res   = sub->residual;
    smp   = sub->samples;
    n     = frame->blocksize;

    /* CONSTANT */
    for (i = 1; i < n; i++)
        if(smp[i] != smp[0])
            break;
    if (i == n) {
        sub->type = sub->type_code = FLAC_SUBFRAME_CONSTANT;
        res[0] = smp[0];
        return subframe_count_exact(s, sub, 0);
    }

    /* VERBATIM */
    if (frame->verbatim_only || n < 5) {
        sub->type = sub->type_code = FLAC_SUBFRAME_VERBATIM;
        memcpy(res, smp, n * sizeof(int32_t));
        return subframe_count_exact(s, sub, 0);
    }

    min_order  = s->options.min_prediction_order;
    max_order  = s->options.max_prediction_order;
    omethod    = s->options.prediction_order_method;

    /* FIXED */
    sub->type = FLAC_SUBFRAME_FIXED;
    if (s->options.lpc_type == FF_LPC_TYPE_NONE  ||
        s->options.lpc_type == FF_LPC_TYPE_FIXED || n <= max_order) {
        uint64_t bits[MAX_FIXED_ORDER+1];
        if (max_order > MAX_FIXED_ORDER)
            max_order = MAX_FIXED_ORDER;
        opt_order = 0;
        bits[0]   = UINT32_MAX;
        for (i = min_order; i <= max_order; i++) {
            encode_residual_fixed(res, smp, n, i);
            bits[i] = find_subframe_rice_params(s, sub, i);
            if (bits[i] < bits[opt_order])
                opt_order = i;
        }
        sub->order     = opt_order;
        sub->type_code = sub->type | sub->order;
        if (sub->order != max_order) {
            encode_residual_fixed(res, smp, n, sub->order);
            find_subframe_rice_params(s, sub, sub->order);
        }
        return subframe_count_exact(s, sub, sub->order);
    }

    /* LPC */
    sub->type = FLAC_SUBFRAME_LPC;
    opt_order = ff_lpc_calc_coefs(&s->lpc_ctx, smp, n, min_order, max_order,
                                  s->options.lpc_coeff_precision, coefs, shift, s->options.lpc_type,
                                  s->options.lpc_passes, omethod,
                                  MIN_LPC_SHIFT, MAX_LPC_SHIFT, 0);

    if (omethod == ORDER_METHOD_2LEVEL ||
        omethod == ORDER_METHOD_4LEVEL ||
        omethod == ORDER_METHOD_8LEVEL) {
        int levels = 1 << omethod;
        uint64_t bits[1 << ORDER_METHOD_8LEVEL];
        int order       = -1;
        int opt_index   = levels-1;
        opt_order       = max_order-1;
        bits[opt_index] = UINT32_MAX;
        for (i = levels-1; i >= 0; i--) {
            int last_order = order;
            order = min_order + (((max_order-min_order+1) * (i+1)) / levels)-1;
            order = av_clip(order, min_order - 1, max_order - 1);
            if (order == last_order)
                continue;
            if (s->bps_code * 4 + s->options.lpc_coeff_precision + av_log2(order) <= 32) {
                s->flac_dsp.lpc16_encode(res, smp, n, order+1, coefs[order],
                                         shift[order]);
            } else {
                s->flac_dsp.lpc32_encode(res, smp, n, order+1, coefs[order],
                                         shift[order]);
            }
            bits[i] = find_subframe_rice_params(s, sub, order+1);
            if (bits[i] < bits[opt_index]) {
                opt_index = i;
                opt_order = order;
            }
        }
        opt_order++;
    } else if (omethod == ORDER_METHOD_SEARCH) {
        // brute-force optimal order search
        uint64_t bits[MAX_LPC_ORDER];
        opt_order = 0;
        bits[0]   = UINT32_MAX;
        for (i = min_order-1; i < max_order; i++) {
            if (s->bps_code * 4 + s->options.lpc_coeff_precision + av_log2(i) <= 32) {
                s->flac_dsp.lpc16_encode(res, smp, n, i+1, coefs[i], shift[i]);
            } else {
                s->flac_dsp.lpc32_encode(res, smp, n, i+1, coefs[i], shift[i]);
            }
            bits[i] = find_subframe_rice_params(s, sub, i+1);
            if (bits[i] < bits[opt_order])
                opt_order = i;
        }
        opt_order++;
    } else if (omethod == ORDER_METHOD_LOG) {
        uint64_t bits[MAX_LPC_ORDER];
        int step;

        opt_order = min_order - 1 + (max_order-min_order)/3;
        memset(bits, -1, sizeof(bits));

        for (step = 16; step; step >>= 1) {
            int last = opt_order;
            for (i = last-step; i <= last+step; i += step) {
                if (i < min_order-1 || i >= max_order || bits[i] < UINT32_MAX)
                    continue;
                if (s->bps_code * 4 + s->options.lpc_coeff_precision + av_log2(i) <= 32) {
                    s->flac_dsp.lpc32_encode(res, smp, n, i+1, coefs[i], shift[i]);
                } else {
                    s->flac_dsp.lpc16_encode(res, smp, n, i+1, coefs[i], shift[i]);
                }
                bits[i] = find_subframe_rice_params(s, sub, i+1);
                if (bits[i] < bits[opt_order])
                    opt_order = i;
            }
        }
        opt_order++;
    }

    if (s->options.multi_dim_quant) {
        int allsteps = 1;
        int i, step, improved;
        int64_t best_score = INT64_MAX;
        int32_t qmax;

        qmax = (1 << (s->options.lpc_coeff_precision - 1)) - 1;

        for (i=0; i<opt_order; i++)
            allsteps *= 3;

        do {
            improved = 0;
            for (step = 0; step < allsteps; step++) {
                int tmp = step;
                int32_t lpc_try[MAX_LPC_ORDER];
                int64_t score = 0;
                int diffsum = 0;

                for (i=0; i<opt_order; i++) {
                    int diff = ((tmp + 1) % 3) - 1;
                    lpc_try[i] = av_clip(coefs[opt_order - 1][i] + diff, -qmax, qmax);
                    tmp /= 3;
                    diffsum += !!diff;
                }
                if (diffsum >8)
                    continue;

                if (s->bps_code * 4 + s->options.lpc_coeff_precision + av_log2(opt_order - 1) <= 32) {
                    s->flac_dsp.lpc16_encode(res, smp, n, opt_order, lpc_try, shift[opt_order-1]);
                } else {
                    s->flac_dsp.lpc32_encode(res, smp, n, opt_order, lpc_try, shift[opt_order-1]);
                }
                score = find_subframe_rice_params(s, sub, opt_order);
                if (score < best_score) {
                    best_score = score;
                    memcpy(coefs[opt_order-1], lpc_try, sizeof(*coefs));
                    improved=1;
                }
            }
        } while(improved);
    }

    sub->order     = opt_order;
    sub->type_code = sub->type | (sub->order-1);
    sub->shift     = shift[sub->order-1];
    for (i = 0; i < sub->order; i++)
        sub->coefs[i] = coefs[sub->order-1][i];

    if (s->bps_code * 4 + s->options.lpc_coeff_precision + av_log2(opt_order) <= 32) {
        s->flac_dsp.lpc16_encode(res, smp, n, sub->order, sub->coefs, sub->shift);
    } else {
        s->flac_dsp.lpc32_encode(res, smp, n, sub->order, sub->coefs, sub->shift);
    }

    find_subframe_rice_params(s, sub, sub->order);

    return subframe_count_exact(s, sub, sub->order);
}