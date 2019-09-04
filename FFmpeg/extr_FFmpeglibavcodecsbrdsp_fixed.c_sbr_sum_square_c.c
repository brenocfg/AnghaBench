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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  SoftFloat ;

/* Variables and functions */
 int INT32_MIN ; 
 int UINT64_MAX ; 
 int /*<<< orphan*/  av_int2sf (unsigned int,int) ; 

__attribute__((used)) static SoftFloat sbr_sum_square_c(int (*x)[2], int n)
{
    SoftFloat ret;
    uint64_t accu = 0, round;
    uint64_t accu0 = 0, accu1 = 0, accu2 = 0, accu3 = 0;
    int i, nz, nz0;
    unsigned u;

    nz = 0;
    for (i = 0; i < n; i += 2) {
        accu0 += (int64_t)x[i + 0][0] * x[i + 0][0];
        accu1 += (int64_t)x[i + 0][1] * x[i + 0][1];
        accu2 += (int64_t)x[i + 1][0] * x[i + 1][0];
        accu3 += (int64_t)x[i + 1][1] * x[i + 1][1];
        if ((accu0|accu1|accu2|accu3) > UINT64_MAX - INT32_MIN*(int64_t)INT32_MIN || i+2>=n) {
            accu0 >>= nz;
            accu1 >>= nz;
            accu2 >>= nz;
            accu3 >>= nz;
            while ((accu0|accu1|accu2|accu3) > (UINT64_MAX - accu) >> 2) {
                accu0 >>= 1;
                accu1 >>= 1;
                accu2 >>= 1;
                accu3 >>= 1;
                accu  >>= 1;
                nz ++;
            }
            accu += accu0 + accu1 + accu2 + accu3;
            accu0 = accu1 = accu2 = accu3 = 0;
        }
    }

    nz0 = 15 - nz;

    u = accu >> 32;
    if (u) {
        nz = 33;
        while (u < 0x80000000U) {
            u <<= 1;
            nz--;
        }
    } else
        nz = 1;

    round = 1ULL << (nz-1);
    u = ((accu + round) >> nz);
    u >>= 1;
    ret = av_int2sf(u, nz0 - nz);

    return ret;
}