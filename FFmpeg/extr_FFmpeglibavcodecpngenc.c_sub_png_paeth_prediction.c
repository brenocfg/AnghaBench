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
 int abs (int) ; 

__attribute__((used)) static void sub_png_paeth_prediction(uint8_t *dst, uint8_t *src, uint8_t *top,
                                     int w, int bpp)
{
    int i;
    for (i = 0; i < w; i++) {
        int a, b, c, p, pa, pb, pc;

        a = src[i - bpp];
        b = top[i];
        c = top[i - bpp];

        p  = b - c;
        pc = a - c;

        pa = abs(p);
        pb = abs(pc);
        pc = abs(p + pc);

        if (pa <= pb && pa <= pc)
            p = a;
        else if (pb <= pc)
            p = b;
        else
            p = c;
        dst[i] = src[i] - p;
    }
}