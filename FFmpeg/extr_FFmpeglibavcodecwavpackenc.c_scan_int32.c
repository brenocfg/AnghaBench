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
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_3__ {int int32_sent_bits; int int32_zeros; int int32_ones; int int32_dups; int flags; int crc_x; } ;
typedef  TYPE_1__ WavPackEncodeContext ;

/* Variables and functions */
 int MAG_LSB ; 
 int MAG_MASK ; 
 int WV_INT32_DATA ; 
 int WV_MONO_DATA ; 
 int /*<<< orphan*/  shift_mono (int*,int,int) ; 
 int /*<<< orphan*/  shift_stereo (int*,int*,int,int) ; 

__attribute__((used)) static int scan_int32(WavPackEncodeContext *s,
                      int32_t *samples_l, int32_t *samples_r,
                      int nb_samples)
{
    uint32_t magdata = 0, ordata = 0, xordata = 0, anddata = ~0;
    uint32_t crc = 0xffffffffu;
    int i, total_shift = 0;

    s->int32_sent_bits = s->int32_zeros = s->int32_ones = s->int32_dups = 0;

    if (s->flags & WV_MONO_DATA) {
        for (i = 0; i < nb_samples; i++) {
            int32_t M = samples_l[i];

            crc = crc * 9 + (M & 0xffff) * 3 + ((M >> 16) & 0xffff);
            magdata |= (M < 0) ? ~M : M;
            xordata |= M ^ -(M & 1);
            anddata &= M;
            ordata  |= M;
        }
    } else {
        for (i = 0; i < nb_samples; i++) {
            int32_t L = samples_l[i];
            int32_t R = samples_r[i];

            crc = crc * 9 + (L & 0xffff) * 3 + ((L >> 16) & 0xffff);
            crc = crc * 9 + (R & 0xffff) * 3 + ((R >> 16) & 0xffff);
            magdata |= (L < 0) ? ~L : L;
            magdata |= (R < 0) ? ~R : R;
            xordata |= L ^ -(L & 1);
            xordata |= R ^ -(R & 1);
            anddata &= L & R;
            ordata  |= L | R;
        }
    }

    s->crc_x = crc;
    s->flags &= ~MAG_MASK;

    while (magdata) {
        s->flags += 1 << MAG_LSB;
        magdata >>= 1;
    }

    if (!((s->flags & MAG_MASK) >> MAG_LSB)) {
        s->flags &= ~WV_INT32_DATA;
        return 0;
    }

    if (!(ordata & 1))
        do {
            s->flags -= 1 << MAG_LSB;
            s->int32_zeros++;
            total_shift++;
            ordata >>= 1;
        } while (!(ordata & 1));
    else if (anddata & 1)
        do {
            s->flags -= 1 << MAG_LSB;
            s->int32_ones++;
            total_shift++;
            anddata >>= 1;
        } while (anddata & 1);
    else if (!(xordata & 2))
        do {
            s->flags -= 1 << MAG_LSB;
            s->int32_dups++;
            total_shift++;
            xordata >>= 1;
        } while (!(xordata & 2));

    if (((s->flags & MAG_MASK) >> MAG_LSB) > 23) {
        s->int32_sent_bits = (uint8_t)(((s->flags & MAG_MASK) >> MAG_LSB) - 23);
        total_shift += s->int32_sent_bits;
        s->flags &= ~MAG_MASK;
        s->flags += 23 << MAG_LSB;
    }

    if (total_shift) {
        s->flags |= WV_INT32_DATA;

        if (s->flags & WV_MONO_DATA)
            shift_mono(samples_l, nb_samples, total_shift);
        else
            shift_stereo(samples_l, samples_r, nb_samples, total_shift);
    }

    return s->int32_sent_bits;
}