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
 int FFMIN3 (int,int,int) ; 
 int* ff_celt_qn_exp2 ; 

__attribute__((used)) static inline int celt_compute_qn(int N, int b, int offset, int pulse_cap,
                                  int stereo)
{
    int qn, qb;
    int N2 = 2 * N - 1;
    if (stereo && N == 2)
        N2--;

    /* The upper limit ensures that in a stereo split with itheta==16384, we'll
     * always have enough bits left over to code at least one pulse in the
     * side; otherwise it would collapse, since it doesn't get folded. */
    qb = FFMIN3(b - pulse_cap - (4 << 3), (b + N2 * offset) / N2, 8 << 3);
    qn = (qb < (1 << 3 >> 1)) ? 1 : ((ff_celt_qn_exp2[qb & 0x7] >> (14 - (qb >> 3))) + 1) >> 1 << 1;
    return qn;
}