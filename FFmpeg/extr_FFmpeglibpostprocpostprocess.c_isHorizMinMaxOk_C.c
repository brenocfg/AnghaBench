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

__attribute__((used)) static inline int isHorizMinMaxOk_C(const uint8_t src[], int stride, int QP)
{
    int i;
    for(i=0; i<2; i++){
        if((unsigned)(src[0] - src[5] + 2*QP) > 4*QP) return 0;
        src += stride;
        if((unsigned)(src[2] - src[7] + 2*QP) > 4*QP) return 0;
        src += stride;
        if((unsigned)(src[4] - src[1] + 2*QP) > 4*QP) return 0;
        src += stride;
        if((unsigned)(src[6] - src[3] + 2*QP) > 4*QP) return 0;
        src += stride;
    }
    return 1;
}