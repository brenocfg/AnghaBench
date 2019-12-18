#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int near; int twonear; int range; size_t* run_index; int* C; int /*<<< orphan*/  maxval; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ JLSState ;

/* Variables and functions */
 int FFABS (int) ; 
 int R (void*,int) ; 
 int /*<<< orphan*/  W (void*,int,int) ; 
 int av_clip (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_jpegls_quantize (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ff_log2_run ; 
 int /*<<< orphan*/  ls_encode_regular (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ls_encode_run (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  ls_encode_runterm (TYPE_1__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int mid_pred (int,int,int) ; 

__attribute__((used)) static inline void ls_encode_line(JLSState *state, PutBitContext *pb,
                                  void *last, void *cur, int last2, int w,
                                  int stride, int comp, int bits)
{
    int x = 0;
    int Ra, Rb, Rc, Rd;
    int D0, D1, D2;

    while (x < w) {
        int err, pred, sign;

        /* compute gradients */
        Ra = x ? R(cur, x - stride) : R(last, x);
        Rb = R(last, x);
        Rc = x ? R(last, x - stride) : last2;
        Rd = (x >= w - stride) ? R(last, x) : R(last, x + stride);
        D0 = Rd - Rb;
        D1 = Rb - Rc;
        D2 = Rc - Ra;

        /* run mode */
        if ((FFABS(D0) <= state->near) &&
            (FFABS(D1) <= state->near) &&
            (FFABS(D2) <= state->near)) {
            int RUNval, RItype, run;

            run    = 0;
            RUNval = Ra;
            while (x < w && (FFABS(R(cur, x) - RUNval) <= state->near)) {
                run++;
                W(cur, x, Ra);
                x += stride;
            }
            ls_encode_run(state, pb, run, comp, x < w);
            if (x >= w)
                return;
            Rb     = R(last, x);
            RItype = FFABS(Ra - Rb) <= state->near;
            pred   = RItype ? Ra : Rb;
            err    = R(cur, x) - pred;

            if (!RItype && Ra > Rb)
                err = -err;

            if (state->near) {
                if (err > 0)
                    err =  (state->near + err) / state->twonear;
                else
                    err = -(state->near - err) / state->twonear;

                if (RItype || (Rb >= Ra))
                    Ra = av_clip(pred + err * state->twonear, 0, state->maxval);
                else
                    Ra = av_clip(pred - err * state->twonear, 0, state->maxval);
                W(cur, x, Ra);
            }
            if (err < 0)
                err += state->range;
            if (err >= state->range + 1 >> 1)
                err -= state->range;

            ls_encode_runterm(state, pb, RItype, err,
                              ff_log2_run[state->run_index[comp]]);

            if (state->run_index[comp] > 0)
                state->run_index[comp]--;
        } else { /* regular mode */
            int context;

            context = ff_jpegls_quantize(state, D0) * 81 +
                      ff_jpegls_quantize(state, D1) *  9 +
                      ff_jpegls_quantize(state, D2);
            pred    = mid_pred(Ra, Ra + Rb - Rc, Rb);

            if (context < 0) {
                context = -context;
                sign    = 1;
                pred    = av_clip(pred - state->C[context], 0, state->maxval);
                err     = pred - R(cur, x);
            } else {
                sign = 0;
                pred = av_clip(pred + state->C[context], 0, state->maxval);
                err  = R(cur, x) - pred;
            }

            if (state->near) {
                if (err > 0)
                    err =  (state->near + err) / state->twonear;
                else
                    err = -(state->near - err) / state->twonear;
                if (!sign)
                    Ra = av_clip(pred + err * state->twonear, 0, state->maxval);
                else
                    Ra = av_clip(pred - err * state->twonear, 0, state->maxval);
                W(cur, x, Ra);
            }

            ls_encode_regular(state, pb, context, err);
        }
        x += stride;
    }
}