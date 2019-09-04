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
struct TYPE_3__ {scalar_t__ QP; } ;
typedef  TYPE_1__ PPContext ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 scalar_t__ FFABS (int) ; 

__attribute__((used)) static inline void doHorizLowPass_C(uint8_t dst[], int stride, const PPContext *c)
{
    int y;
    for(y=0; y<BLOCK_SIZE; y++){
        const int first= FFABS(dst[-1] - dst[0]) < c->QP ? dst[-1] : dst[0];
        const int last= FFABS(dst[8] - dst[7]) < c->QP ? dst[8] : dst[7];

        int sums[10];
        sums[0] = 4*first + dst[0] + dst[1] + dst[2] + 4;
        sums[1] = sums[0] - first  + dst[3];
        sums[2] = sums[1] - first  + dst[4];
        sums[3] = sums[2] - first  + dst[5];
        sums[4] = sums[3] - first  + dst[6];
        sums[5] = sums[4] - dst[0] + dst[7];
        sums[6] = sums[5] - dst[1] + last;
        sums[7] = sums[6] - dst[2] + last;
        sums[8] = sums[7] - dst[3] + last;
        sums[9] = sums[8] - dst[4] + last;

        dst[0]= (sums[0] + sums[2] + 2*dst[0])>>4;
        dst[1]= (sums[1] + sums[3] + 2*dst[1])>>4;
        dst[2]= (sums[2] + sums[4] + 2*dst[2])>>4;
        dst[3]= (sums[3] + sums[5] + 2*dst[3])>>4;
        dst[4]= (sums[4] + sums[6] + 2*dst[4])>>4;
        dst[5]= (sums[5] + sums[7] + 2*dst[5])>>4;
        dst[6]= (sums[6] + sums[8] + 2*dst[6])>>4;
        dst[7]= (sums[7] + sums[9] + 2*dst[7])>>4;

        dst+= stride;
    }
}