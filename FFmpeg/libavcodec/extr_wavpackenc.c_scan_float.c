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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int shifted_ones; int shifted_zeros; int shifted_both; int ordata; int float_shift; int float_flags; int max_exp; int flags; int crc_x; int float_max_exp; scalar_t__ neg_zeros; scalar_t__ false_zeros; } ;
typedef  TYPE_1__ WavPackEncodeContext ;

/* Variables and functions */
 int FLOAT_EXCEPTIONS ; 
 int FLOAT_NEG_ZEROS ; 
 int FLOAT_SHIFT_ONES ; 
 int FLOAT_SHIFT_SAME ; 
 int FLOAT_SHIFT_SENT ; 
 int FLOAT_ZEROS_SENT ; 
 int MAG_LSB ; 
 int MAG_MASK ; 
 int WV_MONO_DATA ; 
 int get_exponent (int /*<<< orphan*/ ) ; 
 int get_mantissa (int /*<<< orphan*/ ) ; 
 int get_sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_float (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shift_mono (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  shift_stereo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int scan_float(WavPackEncodeContext *s,
                      int32_t *samples_l, int32_t *samples_r,
                      int nb_samples)
{
    uint32_t crc = 0xffffffffu;
    int i;

    s->shifted_ones = s->shifted_zeros = s->shifted_both = s->ordata = 0;
    s->float_shift = s->float_flags = 0;
    s->false_zeros = s->neg_zeros = 0;
    s->max_exp = 0;

    if (s->flags & WV_MONO_DATA) {
        for (i = 0; i < nb_samples; i++) {
            int32_t f = samples_l[i];
            crc = crc * 27 + get_mantissa(f) * 9 + get_exponent(f) * 3 + get_sign(f);

            if (get_exponent(f) > s->max_exp && get_exponent(f) < 255)
                s->max_exp = get_exponent(f);
        }
    } else {
        for (i = 0; i < nb_samples; i++) {
            int32_t f;

            f = samples_l[i];
            crc = crc * 27 + get_mantissa(f) * 9 + get_exponent(f) * 3 + get_sign(f);
            if (get_exponent(f) > s->max_exp && get_exponent(f) < 255)
                s->max_exp = get_exponent(f);

            f = samples_r[i];
            crc = crc * 27 + get_mantissa(f) * 9 + get_exponent(f) * 3 + get_sign(f);

            if (get_exponent(f) > s->max_exp && get_exponent(f) < 255)
                s->max_exp = get_exponent(f);
        }
    }

    s->crc_x = crc;

    if (s->flags & WV_MONO_DATA) {
        for (i = 0; i < nb_samples; i++)
            process_float(s, &samples_l[i]);
    } else {
        for (i = 0; i < nb_samples; i++) {
            process_float(s, &samples_l[i]);
            process_float(s, &samples_r[i]);
        }
    }

    s->float_max_exp = s->max_exp;

    if (s->shifted_both)
        s->float_flags |= FLOAT_SHIFT_SENT;
    else if (s->shifted_ones && !s->shifted_zeros)
        s->float_flags |= FLOAT_SHIFT_ONES;
    else if (s->shifted_ones && s->shifted_zeros)
        s->float_flags |= FLOAT_SHIFT_SAME;
    else if (s->ordata && !(s->ordata & 1)) {
        do {
            s->float_shift++;
            s->ordata >>= 1;
        } while (!(s->ordata & 1));

        if (s->flags & WV_MONO_DATA)
            shift_mono(samples_l, nb_samples, s->float_shift);
        else
            shift_stereo(samples_l, samples_r, nb_samples, s->float_shift);
    }

    s->flags &= ~MAG_MASK;

    while (s->ordata) {
        s->flags += 1 << MAG_LSB;
        s->ordata >>= 1;
    }

    if (s->false_zeros || s->neg_zeros)
        s->float_flags |= FLOAT_ZEROS_SENT;

    if (s->neg_zeros)
        s->float_flags |= FLOAT_NEG_ZEROS;

    return s->float_flags & (FLOAT_EXCEPTIONS | FLOAT_ZEROS_SENT |
                             FLOAT_SHIFT_SENT | FLOAT_SHIFT_SAME);
}