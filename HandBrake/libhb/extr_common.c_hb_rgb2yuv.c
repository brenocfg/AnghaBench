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
typedef  double rgb ;

/* Variables and functions */

int hb_rgb2yuv(int rgb)
{
    double r, g, b;
    int y, Cr, Cb;

    r = (rgb >> 16) & 0xff;
    g = (rgb >>  8) & 0xff;
    b = (rgb      ) & 0xff;

    y  =  16. + ( 0.257 * r) + (0.504 * g) + (0.098 * b);
    Cb = 128. + (-0.148 * r) - (0.291 * g) + (0.439 * b);
    Cr = 128. + ( 0.439 * r) - (0.368 * g) - (0.071 * b);

    y = (y < 0) ? 0 : y;
    Cb = (Cb < 0) ? 0 : Cb;
    Cr = (Cr < 0) ? 0 : Cr;

    y = (y > 255) ? 255 : y;
    Cb = (Cb > 255) ? 255 : Cb;
    Cr = (Cr > 255) ? 255 : Cr;

    return (y << 16) | (Cr << 8) | Cb;
}