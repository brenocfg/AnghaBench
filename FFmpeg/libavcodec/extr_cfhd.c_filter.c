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
typedef  size_t ptrdiff_t ;
typedef  int int16_t ;

/* Variables and functions */
 int av_clip_uintp2_c (int,int) ; 

__attribute__((used)) static inline void filter(int16_t *output, ptrdiff_t out_stride,
                          int16_t *low, ptrdiff_t low_stride,
                          int16_t *high, ptrdiff_t high_stride,
                          int len, int clip)
{
    int16_t tmp;
    int i;

    for (i = 0; i < len; i++) {
        if (i == 0) {
            tmp = (11*low[0*low_stride] - 4*low[1*low_stride] + low[2*low_stride] + 4) >> 3;
            output[(2*i+0)*out_stride] = (tmp + high[0*high_stride]) >> 1;
            if (clip)
                output[(2*i+0)*out_stride] = av_clip_uintp2_c(output[(2*i+0)*out_stride], clip);

            tmp = ( 5*low[0*low_stride] + 4*low[1*low_stride] - low[2*low_stride] + 4) >> 3;
            output[(2*i+1)*out_stride] = (tmp - high[0*high_stride]) >> 1;
            if (clip)
                output[(2*i+1)*out_stride] = av_clip_uintp2_c(output[(2*i+1)*out_stride], clip);
        } else if (i == len-1) {
            tmp = ( 5*low[i*low_stride] + 4*low[(i-1)*low_stride] - low[(i-2)*low_stride] + 4) >> 3;
            output[(2*i+0)*out_stride] = (tmp + high[i*high_stride]) >> 1;
            if (clip)
                output[(2*i+0)*out_stride] = av_clip_uintp2_c(output[(2*i+0)*out_stride], clip);

            tmp = (11*low[i*low_stride] - 4*low[(i-1)*low_stride] + low[(i-2)*low_stride] + 4) >> 3;
            output[(2*i+1)*out_stride] = (tmp - high[i*high_stride]) >> 1;
            if (clip)
                output[(2*i+1)*out_stride] = av_clip_uintp2_c(output[(2*i+1)*out_stride], clip);
        } else {
            tmp = (low[(i-1)*low_stride] - low[(i+1)*low_stride] + 4) >> 3;
            output[(2*i+0)*out_stride] = (tmp + low[i*low_stride] + high[i*high_stride]) >> 1;
            if (clip)
                output[(2*i+0)*out_stride] = av_clip_uintp2_c(output[(2*i+0)*out_stride], clip);

            tmp = (low[(i+1)*low_stride] - low[(i-1)*low_stride] + 4) >> 3;
            output[(2*i+1)*out_stride] = (tmp + low[i*low_stride] - high[i*high_stride]) >> 1;
            if (clip)
                output[(2*i+1)*out_stride] = av_clip_uintp2_c(output[(2*i+1)*out_stride], clip);
        }
    }
}