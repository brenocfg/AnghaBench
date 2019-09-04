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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 double fabs (float) ; 
 int /*<<< orphan*/  rgb2rgb565 (int const,int const,int const) ; 

__attribute__((used)) static void optimize_colors(const uint8_t *block, ptrdiff_t stride,
                            uint16_t *pmax16, uint16_t *pmin16)
{
    const uint8_t *minp;
    const uint8_t *maxp;
    const int iter_power = 4;
    double magn;
    int v_r, v_g, v_b;
    float covf[6], vfr, vfg, vfb;
    int mind, maxd;
    int cov[6] = { 0 };
    int mu[3], min[3], max[3];
    int ch, iter, x, y;

    /* Determine color distribution */
    for (ch = 0; ch < 3; ch++) {
        const uint8_t *bp = &block[ch];
        int muv, minv, maxv;

        muv = minv = maxv = bp[0];
        for (y = 0; y < 4; y++) {
            for (x = 4; x < 4; x += 4) {
                muv += bp[x * 4 + y * stride];
                if (bp[x] < minv)
                    minv = bp[x * 4 + y * stride];
                else if (bp[x] > maxv)
                    maxv = bp[x * 4 + y * stride];
            }
        }

        mu[ch]  = (muv + 8) >> 4;
        min[ch] = minv;
        max[ch] = maxv;
    }

    /* Determine covariance matrix */
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            int r = block[x * 4 + stride * y + 0] - mu[0];
            int g = block[x * 4 + stride * y + 1] - mu[1];
            int b = block[x * 4 + stride * y + 2] - mu[2];

            cov[0] += r * r;
            cov[1] += r * g;
            cov[2] += r * b;
            cov[3] += g * g;
            cov[4] += g * b;
            cov[5] += b * b;
        }
    }

    /* Convert covariance matrix to float, find principal axis via power iter */
    for (x = 0; x < 6; x++)
        covf[x] = cov[x] / 255.0f;

    vfr = (float) (max[0] - min[0]);
    vfg = (float) (max[1] - min[1]);
    vfb = (float) (max[2] - min[2]);

    for (iter = 0; iter < iter_power; iter++) {
        float r = vfr * covf[0] + vfg * covf[1] + vfb * covf[2];
        float g = vfr * covf[1] + vfg * covf[3] + vfb * covf[4];
        float b = vfr * covf[2] + vfg * covf[4] + vfb * covf[5];

        vfr = r;
        vfg = g;
        vfb = b;
    }

    magn = fabs(vfr);
    if (fabs(vfg) > magn)
        magn = fabs(vfg);
    if (fabs(vfb) > magn)
        magn = fabs(vfb);

    /* if magnitude is too small, default to luminance */
    if (magn < 4.0f) {
        /* JPEG YCbCr luma coefs, scaled by 1000 */
        v_r = 299;
        v_g = 587;
        v_b = 114;
    } else {
        magn = 512.0 / magn;
        v_r  = (int) (vfr * magn);
        v_g  = (int) (vfg * magn);
        v_b  = (int) (vfb * magn);
    }

    /* Pick colors at extreme points */
    mind = maxd = block[0] * v_r + block[1] * v_g + block[2] * v_b;
    minp = maxp = block;
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            int dot = block[x * 4 + y * stride + 0] * v_r +
                      block[x * 4 + y * stride + 1] * v_g +
                      block[x * 4 + y * stride + 2] * v_b;

            if (dot < mind) {
                mind = dot;
                minp = block + x * 4 + y * stride;
            } else if (dot > maxd) {
                maxd = dot;
                maxp = block + x * 4 + y * stride;
            }
        }
    }

    *pmax16 = rgb2rgb565(maxp[0], maxp[1], maxp[2]);
    *pmin16 = rgb2rgb565(minp[0], minp[1], minp[2]);
}