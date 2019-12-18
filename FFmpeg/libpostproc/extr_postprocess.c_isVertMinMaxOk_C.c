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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int BLOCK_SIZE ; 

__attribute__((used)) static inline int isVertMinMaxOk_C(const uint8_t src[], int stride, int QP)
{
    int x;
    src+= stride*4;
    for(x=0; x<BLOCK_SIZE; x+=4){
        if((unsigned)(src[  x + 0*stride] - src[  x + 5*stride] + 2*QP) > 4*QP) return 0;
        if((unsigned)(src[1+x + 2*stride] - src[1+x + 7*stride] + 2*QP) > 4*QP) return 0;
        if((unsigned)(src[2+x + 4*stride] - src[2+x + 1*stride] + 2*QP) > 4*QP) return 0;
        if((unsigned)(src[3+x + 6*stride] - src[3+x + 3*stride] + 2*QP) > 4*QP) return 0;
    }
    return 1;
}