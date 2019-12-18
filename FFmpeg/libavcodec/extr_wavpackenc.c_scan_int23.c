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
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_3__ {int flags; scalar_t__ int32_dups; scalar_t__ int32_ones; scalar_t__ int32_zeros; scalar_t__ int32_sent_bits; } ;
typedef  TYPE_1__ WavPackEncodeContext ;

/* Variables and functions */
 int MAG_LSB ; 
 int MAG_MASK ; 
 int WV_INT32_DATA ; 
 int WV_MONO_DATA ; 
 int /*<<< orphan*/  shift_mono (int*,int,int) ; 
 int /*<<< orphan*/  shift_stereo (int*,int*,int,int) ; 

__attribute__((used)) static void scan_int23(WavPackEncodeContext *s,
                       int32_t *samples_l, int32_t *samples_r,
                       int nb_samples)
{
    uint32_t magdata = 0, ordata = 0, xordata = 0, anddata = ~0;
    int i, total_shift = 0;

    s->int32_sent_bits = s->int32_zeros = s->int32_ones = s->int32_dups = 0;

    if (s->flags & WV_MONO_DATA) {
        for (i = 0; i < nb_samples; i++) {
            int32_t M = samples_l[i];

            magdata |= (M < 0) ? ~M : M;
            xordata |= M ^ -(M & 1);
            anddata &= M;
            ordata  |= M;

            if ((ordata & 1) && !(anddata & 1) && (xordata & 2))
                return;
        }
    } else {
        for (i = 0; i < nb_samples; i++) {
            int32_t L = samples_l[i];
            int32_t R = samples_r[i];

            magdata |= (L < 0) ? ~L : L;
            magdata |= (R < 0) ? ~R : R;
            xordata |= L ^ -(L & 1);
            xordata |= R ^ -(R & 1);
            anddata &= L & R;
            ordata  |= L | R;

            if ((ordata & 1) && !(anddata & 1) && (xordata & 2))
                return;
        }
    }

    s->flags &= ~MAG_MASK;

    while (magdata) {
        s->flags += 1 << MAG_LSB;
        magdata >>= 1;
    }

    if (!(s->flags & MAG_MASK))
        return;

    if (!(ordata & 1)) {
        do {
            s->flags -= 1 << MAG_LSB;
            s->int32_zeros++;
            total_shift++;
            ordata >>= 1;
        } while (!(ordata & 1));
    } else if (anddata & 1) {
        do {
            s->flags -= 1 << MAG_LSB;
            s->int32_ones++;
            total_shift++;
            anddata >>= 1;
        } while (anddata & 1);
    } else if (!(xordata & 2)) {
        do {
            s->flags -= 1 << MAG_LSB;
            s->int32_dups++;
            total_shift++;
            xordata >>= 1;
        } while (!(xordata & 2));
    }

    if (total_shift) {
        s->flags |= WV_INT32_DATA;

        if (s->flags & WV_MONO_DATA)
            shift_mono(samples_l, nb_samples, total_shift);
        else
            shift_stereo(samples_l, samples_r, nb_samples, total_shift);
    }
}