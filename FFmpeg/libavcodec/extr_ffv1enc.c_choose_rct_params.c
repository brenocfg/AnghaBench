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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint32_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_3__ {int bits_per_raw_sample; int* sample_buffer; int slice_rct_by_coef; int slice_rct_ry_coef; } ;
typedef  TYPE_1__ FFV1Context ;

/* Variables and functions */
 scalar_t__ FFABS (int) ; 
 int NB_Y_COEFF ; 

__attribute__((used)) static void choose_rct_params(FFV1Context *fs, const uint8_t *src[3], const int stride[3], int w, int h)
{
#define NB_Y_COEFF 15
    static const int rct_y_coeff[15][2] = {
        {0, 0}, //      4G
        {1, 1}, //  R + 2G + B
        {2, 2}, // 2R      + 2B
        {0, 2}, //      2G + 2B
        {2, 0}, // 2R + 2G
        {4, 0}, // 4R
        {0, 4}, //           4B

        {0, 3}, //      1G + 3B
        {3, 0}, // 3R + 1G
        {3, 1}, // 3R      +  B
        {1, 3}, //  R      + 3B
        {1, 2}, //  R +  G + 2B
        {2, 1}, // 2R +  G +  B
        {0, 1}, //      3G +  B
        {1, 0}, //  R + 3G
    };

    int stat[NB_Y_COEFF] = {0};
    int x, y, i, p, best;
    int16_t *sample[3];
    int lbd = fs->bits_per_raw_sample <= 8;

    for (y = 0; y < h; y++) {
        int lastr=0, lastg=0, lastb=0;
        for (p = 0; p < 3; p++)
            sample[p] = fs->sample_buffer + p*w;

        for (x = 0; x < w; x++) {
            int b, g, r;
            int ab, ag, ar;
            if (lbd) {
                unsigned v = *((const uint32_t*)(src[0] + x*4 + stride[0]*y));
                b =  v        & 0xFF;
                g = (v >>  8) & 0xFF;
                r = (v >> 16) & 0xFF;
            } else {
                b = *((const uint16_t*)(src[0] + x*2 + stride[0]*y));
                g = *((const uint16_t*)(src[1] + x*2 + stride[1]*y));
                r = *((const uint16_t*)(src[2] + x*2 + stride[2]*y));
            }

            ar = r - lastr;
            ag = g - lastg;
            ab = b - lastb;
            if (x && y) {
                int bg = ag - sample[0][x];
                int bb = ab - sample[1][x];
                int br = ar - sample[2][x];

                br -= bg;
                bb -= bg;

                for (i = 0; i<NB_Y_COEFF; i++) {
                    stat[i] += FFABS(bg + ((br*rct_y_coeff[i][0] + bb*rct_y_coeff[i][1])>>2));
                }

            }
            sample[0][x] = ag;
            sample[1][x] = ab;
            sample[2][x] = ar;

            lastr = r;
            lastg = g;
            lastb = b;
        }
    }

    best = 0;
    for (i=1; i<NB_Y_COEFF; i++) {
        if (stat[i] < stat[best])
            best = i;
    }

    fs->slice_rct_by_coef = rct_y_coeff[best][1];
    fs->slice_rct_ry_coef = rct_y_coeff[best][0];
}