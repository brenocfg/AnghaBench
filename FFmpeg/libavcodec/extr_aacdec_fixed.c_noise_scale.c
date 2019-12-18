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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int* exp2tab ; 

__attribute__((used)) static void noise_scale(int *coefs, int scale, int band_energy, int len)
{
    int s = -scale;
    unsigned int round;
    int i, out, c = exp2tab[s & 3];
    int nlz = 0;

    av_assert0(s >= 0);
    while (band_energy > 0x7fff) {
        band_energy >>= 1;
        nlz++;
    }
    c /= band_energy;
    s = 21 + nlz - (s >> 2);

    if (s > 31) {
        for (i=0; i<len; i++) {
            coefs[i] = 0;
        }
    } else if (s >= 0) {
        round = s ? 1 << (s-1) : 0;
        for (i=0; i<len; i++) {
            out = (int)(((int64_t)coefs[i] * c) >> 32);
            coefs[i] = -((int)(out+round) >> s);
        }
    }
    else {
        s = s + 32;
        if (s > 0) {
            round = 1 << (s-1);
            for (i=0; i<len; i++) {
                out = (int)((int64_t)((int64_t)coefs[i] * c + round) >> s);
                coefs[i] = -out;
            }
        } else {
            for (i=0; i<len; i++)
                coefs[i] = -(int64_t)coefs[i] * c * (1 << -s);
        }
    }
}