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
typedef  int ptrdiff_t ;
typedef  int int16_t ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 int av_clip (int,int,int) ; 

__attribute__((used)) static void filter181(int16_t *data, int width, int height, ptrdiff_t stride)
{
    int x, y;

    /* horizontal filter */
    for (y = 1; y < height - 1; y++) {
        int prev_dc = data[0 + y * stride];

        for (x = 1; x < width - 1; x++) {
            int dc;
            dc = -prev_dc +
                 data[x     + y * stride] * 8 -
                 data[x + 1 + y * stride];
            dc = (av_clip(dc, INT_MIN/10923, INT_MAX/10923 - 32768) * 10923 + 32768) >> 16;
            prev_dc = data[x + y * stride];
            data[x + y * stride] = dc;
        }
    }

    /* vertical filter */
    for (x = 1; x < width - 1; x++) {
        int prev_dc = data[x];

        for (y = 1; y < height - 1; y++) {
            int dc;

            dc = -prev_dc +
                 data[x +  y      * stride] * 8 -
                 data[x + (y + 1) * stride];
            dc = (av_clip(dc, INT_MIN/10923, INT_MAX/10923 - 32768) * 10923 + 32768) >> 16;
            prev_dc = data[x + y * stride];
            data[x + y * stride] = dc;
        }
    }
}