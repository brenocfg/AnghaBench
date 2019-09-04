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
 int FIX (double) ; 
 int ONE_HALF ; 
 int SCALEBITS ; 

__attribute__((used)) static void rgb24_to_yuv420p(unsigned char *lum, unsigned char *cb,
                             unsigned char *cr, const unsigned char *src,
                             int width, int height)
{
    int wrap, wrap3, x, y;
    int r, g, b, r1, g1, b1;
    const unsigned char *p;

    wrap  = width;
    wrap3 = width * 3;
    p     = src;
    for (y = 0; y < height; y += 2) {
        for (x = 0; x < width; x += 2) {
            r       = p[0];
            g       = p[1];
            b       = p[2];
            r1      = r;
            g1      = g;
            b1      = b;
            lum[0]  = (FIX(0.29900) * r + FIX(0.58700) * g +
                       FIX(0.11400) * b + ONE_HALF) >> SCALEBITS;
            r       = p[3];
            g       = p[4];
            b       = p[5];
            r1     += r;
            g1     += g;
            b1     += b;
            lum[1]  = (FIX(0.29900) * r + FIX(0.58700) * g +
                       FIX(0.11400) * b + ONE_HALF) >> SCALEBITS;
            p      += wrap3;
            lum    += wrap;

            r       = p[0];
            g       = p[1];
            b       = p[2];
            r1     += r;
            g1     += g;
            b1     += b;
            lum[0]  = (FIX(0.29900) * r + FIX(0.58700) * g +
                       FIX(0.11400) * b + ONE_HALF) >> SCALEBITS;
            r       = p[3];
            g       = p[4];
            b       = p[5];
            r1     += r;
            g1     += g;
            b1     += b;
            lum[1]  = (FIX(0.29900) * r + FIX(0.58700) * g +
                       FIX(0.11400) * b + ONE_HALF) >> SCALEBITS;

            cb[0]   = ((- FIX(0.16874) * r1 - FIX(0.33126) * g1 +
                       FIX(0.50000) * b1 + 4 * ONE_HALF - 1) >> (SCALEBITS + 2)) + 128;
            cr[0]   = ((FIX(0.50000) * r1 - FIX(0.41869) * g1 -
                       FIX(0.08131) * b1 + 4 * ONE_HALF - 1) >> (SCALEBITS + 2)) + 128;

            cb++;
            cr++;
            p   += -wrap3 + 2 * 3;
            lum += -wrap  + 2;
        }
        p   += wrap3;
        lum += wrap;
    }
}