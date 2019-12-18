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
typedef  int int16_t ;
struct TYPE_3__ {int pf_gain; } ;
typedef  TYPE_1__ G723_1_ChannelContext ;

/* Variables and functions */
 int SUBFRAME_LEN ; 
 int av_clip_int16 (int) ; 
 int av_clip_uintp2 (int,int) ; 
 int av_sat_dadd32 (int,int) ; 
 int ff_g723_1_normalize_bits (int,int) ; 
 int square_root (int) ; 

__attribute__((used)) static void gain_scale(G723_1_ChannelContext *p, int16_t * buf, int energy)
{
    int num, denom, gain, bits1, bits2;
    int i;

    num   = energy;
    denom = 0;
    for (i = 0; i < SUBFRAME_LEN; i++) {
        int temp = buf[i] >> 2;
        temp *= temp;
        denom = av_sat_dadd32(denom, temp);
    }

    if (num && denom) {
        bits1   = ff_g723_1_normalize_bits(num,   31);
        bits2   = ff_g723_1_normalize_bits(denom, 31);
        num     = num << bits1 >> 1;
        denom <<= bits2;

        bits2 = 5 + bits1 - bits2;
        bits2 = av_clip_uintp2(bits2, 5);

        gain = (num >> 1) / (denom >> 16);
        gain = square_root(gain << 16 >> bits2);
    } else {
        gain = 1 << 12;
    }

    for (i = 0; i < SUBFRAME_LEN; i++) {
        p->pf_gain = (15 * p->pf_gain + gain + (1 << 3)) >> 4;
        buf[i]     = av_clip_int16((buf[i] * (p->pf_gain + (p->pf_gain >> 4)) +
                                   (1 << 10)) >> 11);
    }
}