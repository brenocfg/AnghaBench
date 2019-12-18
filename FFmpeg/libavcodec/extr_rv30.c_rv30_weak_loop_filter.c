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
typedef  int uint8_t ;

/* Variables and functions */
 int MAX_NEG_CROP ; 
 int av_clip (int,int const,int const) ; 
 int* ff_crop_tab ; 

__attribute__((used)) static inline void rv30_weak_loop_filter(uint8_t *src, const int step,
                                         const int stride, const int lim)
{
    const uint8_t *cm = ff_crop_tab + MAX_NEG_CROP;
    int i, diff;

    for(i = 0; i < 4; i++){
        diff = ((src[-2*step] - src[1*step]) - (src[-1*step] - src[0*step])*4) >> 3;
        diff = av_clip(diff, -lim, lim);
        src[-1*step] = cm[src[-1*step] + diff];
        src[ 0*step] = cm[src[ 0*step] - diff];
        src += stride;
    }
}