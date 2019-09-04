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
struct TYPE_5__ {scalar_t__* aw_n_pulses; int aw_pulse_range; scalar_t__* aw_first_pulse_off; scalar_t__ aw_idx_is_ext; } ;
typedef  TYPE_1__ WMAVoiceContext ;
struct TYPE_6__ {double* y; size_t n; scalar_t__* x; scalar_t__ pitch_lag; int no_repeat_mask; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AMRFixed ;

/* Variables and functions */
 int MAX_FRAMESIZE ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void aw_pulse_set1(WMAVoiceContext *s, GetBitContext *gb,
                          int block_idx, AMRFixed *fcb)
{
    int val = get_bits(gb, 12 - 2 * (s->aw_idx_is_ext && !block_idx));
    float v;

    if (s->aw_n_pulses[block_idx] > 0) {
        int n, v_mask, i_mask, sh, n_pulses;

        if (s->aw_pulse_range == 24) { // 3 pulses, 1:sign + 3:index each
            n_pulses = 3;
            v_mask   = 8;
            i_mask   = 7;
            sh       = 4;
        } else { // 4 pulses, 1:sign + 2:index each
            n_pulses = 4;
            v_mask   = 4;
            i_mask   = 3;
            sh       = 3;
        }

        for (n = n_pulses - 1; n >= 0; n--, val >>= sh) {
            fcb->y[fcb->n] = (val & v_mask) ? -1.0 : 1.0;
            fcb->x[fcb->n] = (val & i_mask) * n_pulses + n +
                                 s->aw_first_pulse_off[block_idx];
            while (fcb->x[fcb->n] < 0)
                fcb->x[fcb->n] += fcb->pitch_lag;
            if (fcb->x[fcb->n] < MAX_FRAMESIZE / 2)
                fcb->n++;
        }
    } else {
        int num2 = (val & 0x1FF) >> 1, delta, idx;

        if (num2 < 1 * 79)      { delta = 1; idx = num2 + 1; }
        else if (num2 < 2 * 78) { delta = 3; idx = num2 + 1 - 1 * 77; }
        else if (num2 < 3 * 77) { delta = 5; idx = num2 + 1 - 2 * 76; }
        else                    { delta = 7; idx = num2 + 1 - 3 * 75; }
        v = (val & 0x200) ? -1.0 : 1.0;

        fcb->no_repeat_mask |= 3 << fcb->n;
        fcb->x[fcb->n]       = idx - delta;
        fcb->y[fcb->n]       = v;
        fcb->x[fcb->n + 1]   = idx;
        fcb->y[fcb->n + 1]   = (val & 1) ? -v : v;
        fcb->n              += 2;
    }
}