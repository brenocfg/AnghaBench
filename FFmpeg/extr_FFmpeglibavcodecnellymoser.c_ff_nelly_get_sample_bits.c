#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int FFABS (int) ; 
 int FFMAX (int,float const) ; 
 int NELLY_BASE_OFF ; 
 short NELLY_BASE_SHIFT ; 
 int /*<<< orphan*/  NELLY_BIT_CAP ; 
 short NELLY_DETAIL_BITS ; 
 int NELLY_FILL_LEN ; 
 scalar_t__ abs (int) ; 
 int av_clip (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ headroom (int*) ; 
 void* signed_shift (float const,short) ; 
 int sum_bits (short*,short,int) ; 

void ff_nelly_get_sample_bits(const float *buf, int *bits)
{
    int i, j;
    short sbuf[128];
    int bitsum = 0, last_bitsum, small_bitsum, big_bitsum;
    short shift, shift_saved;
    int max, sum, last_off, tmp;
    int big_off, small_off;
    int off;

    max = 0;
    for (i = 0; i < NELLY_FILL_LEN; i++) {
        max = FFMAX(max, buf[i]);
    }
    shift = -16;
    shift += headroom(&max);

    sum = 0;
    for (i = 0; i < NELLY_FILL_LEN; i++) {
        sbuf[i] = signed_shift(buf[i], shift);
        sbuf[i] = (3*sbuf[i])>>2;
        sum += sbuf[i];
    }

    shift += 11;
    shift_saved = shift;
    sum -= NELLY_DETAIL_BITS << shift;
    shift += headroom(&sum);
    small_off = (NELLY_BASE_OFF * (sum>>16)) >> 15;
    shift = shift_saved - (NELLY_BASE_SHIFT+shift-31);

    small_off = signed_shift(small_off, shift);

    bitsum = sum_bits(sbuf, shift_saved, small_off);

    if (bitsum != NELLY_DETAIL_BITS) {
        off = bitsum - NELLY_DETAIL_BITS;

        for(shift=0; FFABS(off) <= 16383; shift++)
            off *= 2;

        off = (off * NELLY_BASE_OFF) >> 15;
        shift = shift_saved-(NELLY_BASE_SHIFT+shift-15);

        off = signed_shift(off, shift);

        for (j = 1; j < 20; j++) {
            last_off = small_off;
            small_off += off;
            last_bitsum = bitsum;

            bitsum = sum_bits(sbuf, shift_saved, small_off);

            if ((bitsum-NELLY_DETAIL_BITS) * (last_bitsum-NELLY_DETAIL_BITS) <= 0)
                break;
        }

        if (bitsum > NELLY_DETAIL_BITS) {
            big_off = small_off;
            small_off = last_off;
            big_bitsum=bitsum;
            small_bitsum=last_bitsum;
        } else {
            big_off = last_off;
            big_bitsum=last_bitsum;
            small_bitsum=bitsum;
        }

        while (bitsum != NELLY_DETAIL_BITS && j <= 19) {
            off = (big_off+small_off)>>1;
            bitsum = sum_bits(sbuf, shift_saved, off);
            if (bitsum > NELLY_DETAIL_BITS) {
                big_off=off;
                big_bitsum=bitsum;
            } else {
                small_off = off;
                small_bitsum=bitsum;
            }
            j++;
        }

        if (abs(big_bitsum-NELLY_DETAIL_BITS) >=
            abs(small_bitsum-NELLY_DETAIL_BITS)) {
            bitsum = small_bitsum;
        } else {
            small_off = big_off;
            bitsum = big_bitsum;
        }
    }

    for (i = 0; i < NELLY_FILL_LEN; i++) {
        tmp = sbuf[i]-small_off;
        tmp = ((tmp>>(shift_saved-1))+1)>>1;
        bits[i] = av_clip(tmp, 0, NELLY_BIT_CAP);
    }

    if (bitsum > NELLY_DETAIL_BITS) {
        tmp = i = 0;
        while (tmp < NELLY_DETAIL_BITS) {
            tmp += bits[i];
            i++;
        }

        bits[i-1] -= tmp - NELLY_DETAIL_BITS;
        for(; i < NELLY_FILL_LEN; i++)
            bits[i] = 0;
    }
}